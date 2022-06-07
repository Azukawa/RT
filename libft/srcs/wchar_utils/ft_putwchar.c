/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:02:03 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:18:49 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
**	fileformat.info/info/unicode/utf8.htm
**	First bit will have as many bits as there are bytes total set [1]
**	with one following bit clear [0] (11110xxx for a 4-byte character).
**	Following bytes have first bit set with one following bit clear (10xxxxxx).
**
**	Most significant bits are always shifted right and rest are zeroed
**	with UTF-8 encoding added in front.
**	0xF0 = first byte of a four-byte sequence		|| 0x07 masks last 3 bits
**	0xE0 = first byte of a three-byte sequence		|| 0x0F masks last 4 bits
**	0xC0 = first byte of a two-byte sequence		|| 0x1F masks last 5 bits
**	0x80 = continuing byte in a multi-byte sequence	|| 0x3F masks last 6 bits
*/

static void	write_utf8(wint_t c, int size, int fd)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)malloc(sizeof(unsigned char) * size);
	if (!tmp)
		return ;
	if (size == 4)
		tmp[0] = ((c >> 18) & 0x07) | 0xF0;
	if (size == 4)
		tmp[1] = ((c >> 12) & 0x3F) | 0x80;
	if (size == 3)
		tmp[0] = ((c >> 12) & 0x0F) | 0xE0;
	if (size == 2)
		tmp[0] = ((c >> 6) & 0x1F) | 0xC0;
	else
		tmp[size - 2] = ((c >> 6) & 0x3F) | 0x80;
	tmp[size - 1] = (c & 0x3F) | 0x80;
	write(fd, &tmp, size);
	free(tmp);
}

/*
**	Values lower than 128 are ASCII compatible so we can write them directly.
*/

void	ft_putwchar(wint_t wc, int fd)
{
	if (wc >= 0x10000)
		write_utf8(wc, 4, fd);
	else if (wc >= 0x800)
		write_utf8(wc, 3, fd);
	else if (wc >= 0x80)
		write_utf8(wc, 2, fd);
	else
		write(fd, &wc, 1);
}
