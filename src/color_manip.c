/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:21:54 by eniini            #+#    #+#             */
/*   Updated: 2022/04/15 21:32:54 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
**	Lineal interpolation calculation using floating point values.
**	Handles precision differences between arguments by dividing
**	the multiplications between [p] and [a/b] in two parts.
*/
static double	lerpf(float a, float b, float p)
{
	if (a == b)
		return (a);
	if (p == 1)
		return (b);
	if (!(p))
		return (a);
	return ((a * (1.0f - p)) + (b * p));
}

/*
*	Clamps the float [value] between [min] & [max].
*/
static double	clampf(float value, float min, float max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}

//convert t_color to ARGB uint for SDL pixel painting
uint32_t	col_to_uint(t_color color)
{
	uint8_t	ir;
	uint8_t	ig;
	uint8_t	ib;

	ir = (uint8_t)(255 * clampf(color.red, 0.0f, 1.0f));
	ig = (uint8_t)(255 * clampf(color.green, 0.0f, 1.0f));
	ib = (uint8_t)(255 * clampf(color.blue, 0.0f, 1.0f));
	return (255 << 24 | ir << 16 | ig << 8 | ib);
}

//linear interpolation of two t_color structs.
t_color	col_lerp(t_color c1, t_color c2, float p)
{
	t_color	result;

	if (p < 0.0f)
		p = 0.0f;
	if (p > 1.0f)
		p = 1.0f;
	result.red = lerpf(c1.red, c2.red, p);
	result.green = lerpf(c1.green, c2.green, p);
	result.blue = lerpf(c1.blue, c2.blue, p);
	return (result);
}

//mix/blend two colors together
t_color	col_blend(t_color base, t_color mix, float p)
{
	t_color	result;
	float	pm;

	if (p < 0.0f)
		p = 0.0f;
	if (p > 1.0f)
		p = 1.0f;
	pm = 1.0f - p;
	result.red = pm * base.red + p * mix.red;
	result.green = pm * base.green + p * mix.green;
	result.blue = pm * base.blue + p * mix.blue;
	return (result);
}

t_color	col_multiply(t_color color, float m)
{
	t_color	result;

	result.red = clampf(color.red * m, 0.0f, 1.0f);
	result.green = clampf(color.green * m, 0.0f, 1.0f);
	result.blue = clampf(color.blue * m, 0.0f, 1.0f);
	return (result);
}

t_color	col_substract(t_color base, t_color mix, float p)
{
	t_color	result;

	if (p == 0.0f)
		return (base);
	if (p == 1.0f)
	{
		result.red = clampf(base.red - mix.red, 0.0f, 1.0f);
		result.green = clampf(base.green - mix.green, 0.0f, 1.0f);
		result.blue = clampf(base.blue - mix.blue, 0.0f, 1.0f);
		return (result);
	}
	result.red = clampf(base.red - (p * mix.red), 0.0f, 1.0f);
	result.green = clampf(base.green - (p * mix.green), 0.0f, 1.0f);
	result.blue = clampf(base.blue - (p * mix.blue), 0.0f, 1.0f);
	return (result);
}

t_color	col_add(t_color base, t_color mix, float p)
{
	t_color	result;

	if (p == 0.0f)
		return (base);
	if (p == 1.0f)
	{
		result.red = clampf(base.red + mix.red, 0.0f, 1.0f);
		result.green = clampf(base.green + mix.green, 0.0f, 1.0f);
		result.blue = clampf(base.blue + mix.blue, 0.0f, 1.0f);
		return (result);
	}
	result.red = clampf(base.red + (p * mix.red), 0.0f, 1.0f);
	result.green = clampf(base.green + (p * mix.green), 0.0f, 1.0f);
	result.blue = clampf(base.blue + (p * mix.blue), 0.0f, 1.0f);
	return (result);
}
