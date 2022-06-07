/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:21 by esukava           #+#    #+#             */
/*   Updated: 2022/05/29 15:27:18 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
*	Colors the pixel in given coordinates of the given buffer as the given
*	hexadecimal value [0xAARRGGBB]. (00 for AA being zero transparency)
*/
void	draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color)
{
	uint32_t	i;

	i = (buf->w * y) + x;
	if (x < buf->w && y < buf->h)
		buf->px[i] = color;
}
