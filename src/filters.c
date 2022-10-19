/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grayscale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:54:58 by eniini            #+#    #+#             */
/*   Updated: 2022/05/29 15:27:22 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
*	Calculates 'truer', gamma-corrected perceived brightness of the given color.
*	Linearized values are weighed for their hue and added together, then
*	de-linearized back to sRGB space.
*
*	2.2 Power Curve is used to extract true value of a gamma-encoded color value
*	[R weighted 0.2126] / [G weighted 0.7152] / [B weighted 0.0722] reflects
*	human color sensitivity.
*/
static uint32_t	grayscale(uint32_t c)
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
	v = (uint8_t)powf(0.2126f * powf(r, 2.2f) + 0.7152f * powf(g, 2.2f) \
	+ 0.0722f * powf(b, 2.2f), 1 / 2.2f);
	return ((a << 24) | (v << 16) | (v << 8) | v);
}

static uint32_t	seepia(uint32_t c)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	a = c >> 24 & 255;
	r = c >> 16 & 255;
	g = c >> 8 & 255;
	b = c & 255;
	return ((a << 24)
		| ft_clamp_i((r * 0.393) + (g * 0.769) + (b * 0.189), 0, 255) << 16
		| ft_clamp_i((r * 0.349) + (g * 0.686) + (b * 0.168), 0, 255) << 8
		| ft_clamp_i((r * 0.272) + (g * 0.534) + (b * 0.131), 0, 255));
}

static uint32_t	invert(uint32_t c)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	a = 255 - (c >> 24 & 255);
	r = 255 - (c >> 16 & 255);
	g = 255 - (c >> 8 & 255);
	b = 255 - (c & 255);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

uint32_t	convert_to(uint32_t c, uint *i)
{
	if (*i > 3)
		*i = 0;
	if (*i == 0)
		return (c);
	if (*i == 1)
		return (grayscale(c));
	if (*i == 2)
		return (seepia(c));
	return (invert(c));
}
