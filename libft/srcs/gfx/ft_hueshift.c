/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hueshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:31:07 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:55:13 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gfx.h"

/*
**	Since RGB values effectively form a cube of color space, we're able to
**	shift a hue of a 'color point' by applying an axis+angle rotation matrix.
**	[axis_unit] is a simplified constant for axis vector calculations.
**
**	Since mlx color is stored as int, final calculation of values is rounded up
**	to preserve original brightness level.
**
**	Return values are clamped since diagonal of RGB cube and its rotation
**	result in values outside a 255³.
*/

int	ft_hueshift(int c, double p)
{
	t_rgb_mat	mat;
	int			rx;
	int			gx;
	int			bx;

	mat.cos_a = cos(p * DEG_TO_RAD);
	mat.sin_a = sin(p * DEG_TO_RAD);
	mat.axis_unit = sqrt(1. / 3.);
	mat.rix[0][0] = mat.cos_a + (1.0 - mat.cos_a) / 3.0;
	mat.rix[0][1] = 1. / 3. * (1.0 - mat.cos_a) - mat.axis_unit * mat.sin_a;
	mat.rix[0][2] = 1. / 3. * (1.0 - mat.cos_a) + mat.axis_unit * mat.sin_a;
	mat.rix[1][0] = 1. / 3. * (1.0 - mat.cos_a) + mat.axis_unit * mat.sin_a;
	mat.rix[1][1] = mat.cos_a + 1. / 3. * (1.0 - mat.cos_a);
	mat.rix[1][2] = 1. / 3. * (1.0 - mat.cos_a) - mat.axis_unit * mat.sin_a;
	mat.rix[2][0] = 1. / 3. * (1.0 - mat.cos_a) - mat.axis_unit * mat.sin_a;
	mat.rix[2][1] = 1. / 3. * (1.0 - mat.cos_a) + mat.axis_unit * mat.sin_a;
	mat.rix[2][2] = mat.cos_a + 1. / 3. * (1.0 - mat.cos_a);
	rx = round(((c >> 16) & 255) * mat.rix[0][0] + ((c >> 8) & 255)
			* mat.rix[0][1] + (c & 255) * mat.rix[0][2]);
	gx = round(((c >> 16) & 255) * mat.rix[1][0] + ((c >> 8) & 255)
			* mat.rix[1][1] + (c & 255) * mat.rix[1][2]);
	bx = round(((c >> 16) & 255) * mat.rix[2][0] + ((c >> 8) & 255)
			* mat.rix[2][1] + (c & 255) * mat.rix[2][2]);
	return (0 << 24 | ft_clamp_i(rx, 0, 255) << 16
		| ft_clamp_i(gx, 0, 255) << 8 | ft_clamp_i(bx, 0, 255));
}
