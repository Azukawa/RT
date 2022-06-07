/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 21:58:16 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:55:59 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Naive implementation of loading an uncompressed bitmap into memory.
*	Does not include full BMP format support, only [BITMAPINFOHEADER] is tested
*	to work. Extracts necessary metadata by bitshifting predetermined data
*	positions into a single integer. If no total image size is found,
*	program assumes it to be (width * length * bpp / 8).
*/

#include <unistd.h>
#include <fcntl.h>
#include "ft_gfx.h"

/*
*	BMP format loads bytes from left to right and from bottom to up.
*	Therefore we need to reverse the line order of given data by
*	swapping each row with its opposite.
*/
static t_gfxinfo	*flip_scanlines(t_gfxinfo *bmp)
{
	int	i;
	int	unit;
	int	len;

	i = 0;
	unit = bmp->bpp / 8;
	len = bmp->img_h * bmp->img_w * unit;
	while (i < len / 2)
	{
		ft_swap(&bmp->one_d_addr[i],
			&bmp->one_d_addr[len - (bmp->img_w * unit) - i], bmp->img_w * unit);
		i += bmp->img_w * unit;
	}
	bmp->two_d_addr = NULL;
	return (bmp);
}

/*
*	Previous read() call increments file descriptor pointer past .BMP metadata,
*	so the next call is assumed to read all of the pixel data insid the file.
*/
static t_gfxinfo	*read_data(t_gfxinfo *bmp, unsigned int imgsize, int fd)
{
	bmp->one_d_addr = malloc(sizeof(unsigned char) * imgsize);
	if (!bmp->one_d_addr)
	{
		free(bmp);
		return (NULL);
	}
	if (read(fd, bmp->one_d_addr, imgsize) != imgsize)
	{
		free(bmp->one_d_addr);
		free(bmp);
		return (NULL);
	}
	close(fd);
	return (flip_scanlines(bmp));
}

/*
*	Loads the raw pixel data of given .BMP file into a [gfxinfo] struct.
*	Pixel data is stored into the [gfxinfo->one_d_addr] pointer as an
*	unsigned char array.
*/
t_gfxinfo	*ft_load_bmp(const char *imagepath)
{
	t_gfxinfo		*i;
	unsigned char	h[54];
	unsigned int	imgsize;
	int				fd;

	fd = open(imagepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read(fd, h, 54) != 54)
		return (NULL);
	if (h[0] != 'B' || h[1] != 'M')
		return (NULL);
	i = malloc(sizeof(t_gfxinfo));
	if (!i)
		return (NULL);
	i->img_w = h[0x12] | (h[0x13] << 8) | (h[0x14] << 16) | (h[0x15] << 24);
	i->img_h = h[0x16] | (h[0x17] << 8) | (h[0x18] << 16) | (h[0x19] << 24);
	i->bpp = h[0x1C] | (h[0x1D] << 8);
	imgsize = h[0x22] | (h[0x23] << 8) | (h[0x24] << 16) | (h[0x25] << 24);
	if (!imgsize)
		imgsize = i->img_w * i->img_h * (i->bpp / 8);
	return (read_data(i, imgsize, fd));
}
