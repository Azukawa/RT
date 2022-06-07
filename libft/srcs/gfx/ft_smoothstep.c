/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smoothstep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:54:11 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:03 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gfx.h"

/*
**	Uses Hermite interpolation to create smooth transition between the
**	[start] & [end] points. Returns a value between 0 and 1.
**
**	khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.1.40.pdf#page=81
*/
double	ft_smoothstep(double start, double end, double x)
{
	if (x < start)
		return (0.0);
	if (x > end)
		return (1.0);
	x = ft_clamp_d((x - start) / (end - start), 0.0, 1.0);
	return (x * x * (3.0 - 2.0 * x));
}
