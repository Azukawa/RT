/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argb_grayscale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:03:13 by eniini            #+#    #+#             */
/*   Updated: 2021/06/21 19:05:22 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gfx.h"

/*
*	Calculates the perceived brightness (luma) of a given color.
*/
uint32_t	ft_argb_grayscale(uint32_t c)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	v;

	a = c >> 24 & 255;
	r = c >> 16 & 255;
	g = c >> 8 & 255;
	b = c & 255;
	v = (0.2126 * r) + (0.7152 * g) + (0.0722 * b);
	return ((a << 24) | (v << 16) | (v << 8) | v);
}

/*
*	Calculates 'truer', gamma-corrected perceived brightness of the given color.
*	Linearized values are weighed for their hue and added together, then
*	de-linearized back to sRGB space.
*/
uint32_t	ft_argb_realgrayscale(uint32_t c)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	v;

	a = c >> 24 & 255;
	r = c >> 16 & 255;
	g = c >> 8 & 255;
	b = c & 255;
	v = pow(0.2126 * pow(r, 2.4) + 0.7152 * pow(g, 2.4) + 0.0722
			* pow(b, 2.4), 1 / 2.4);
	return ((a << 24) | (v << 16) | (v << 8) | v);
}
