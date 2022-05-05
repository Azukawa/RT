/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:42 by eniini            #+#    #+#             */
/*   Updated: 2022/05/05 20:37:08 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
*	Returns a color corresponding to a checkered pattern. [Scale] directly
*	corresponds to how many tiles are generated onto the plane.
*
*	note: dividing [y] by half is a hacky way to solve issues with aspect ratio.
*/
t_color	apply_check_pattern(t_rt *rt, float scale, float x, float y)
{
	t_bool	yresult;
	t_bool	xresult;
	t_bool	result;

	y *= 0.5f;
	if (((y * scale) - floorf(y * scale)) < 0.5f)
		yresult = TRUE;
	else
		yresult = FALSE;
	if (((x * scale) - floorf(x * scale)) < 0.5f)
		xresult = TRUE;
	else
		xresult = FALSE;
	result = (xresult ^ yresult);
	if (result)
		return ((t_color){0,0,0});
	else
		return ((t_color){1,1,1});
}

t_color	apply_texture(t_rt *rt, float x, float y)
{
	float	a = 20.0f;
	float	b = 50.0f;
	float	t = (a * x + b * y);
	float	s = t - floorf(t);
	//float	s = 1.0f + sinf(t) / 2.0f;
	return (col_blend((t_color){0,0,0}, (t_color){1,1,1}, s));
	//(1.0+sin(t))/2.0, abs(sin(t)) and (t−floor(t))

}

/*
*	[pos] is assumed to be a point in the surface of the sphere.
*/
t_fvector	spherical_map(t_fvector pos, t_fvector hit_point, t_object sphere)
{
	float		theta = atan2f(pos.x, pos.z); //arctan2(pos.x, pos.z);
	float		radius = v_len(v_sub(hit_point, sphere.pos));
 	float		phi = acosf(pos.y / radius); // = arccos(pos.y / radius);
	float		raw_u = theta / (2.0f * M_PI);
	t_fvector	ret;
	// 0 <= u < 1
	// here's also where we fix the direction of u. Subtract it from 1,
	// so that it increases counterclockwise as viewed from above.
	ret.x = 1.0f - (raw_u + 0.5);

	// we want v to be 0 at the south pole of the sphere,
	// and 1 at the north pole, so we have to "flip it over"
	// by subtracting it from 1.
	ret.y = 1.0f - phi / M_PI;
	ret.z = 0;
	return (ret);
}