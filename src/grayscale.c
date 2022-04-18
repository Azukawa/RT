/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grayscale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:54:58 by eniini            #+#    #+#             */
/*   Updated: 2022/04/15 21:33:02 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
*	Calculates 'truer', gamma-corrected perceived brightness of the given color.
*	Linearized values are weighed for their hue and added together, then
*	de-linearized back to sRGB space.
*
*	2.2 Power Curve is used to extract true value of a gamma-encoded color value
*	[R weighted 0.2126] / [G weighted 0.7152] / [B weighted 0.0722] reflects
*	human color sensitivity.
*/
uint32_t	convert_to_grayscale(uint32_t c)
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
