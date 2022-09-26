/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:20:56 by alero             #+#    #+#             */
/*   Updated: 2022/09/25 19:05:30 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
*	Returns a color corresponding to a checkered pattern. [Scale] directly
*	corresponds to how many tiles are generated onto the plane.
*/
t_color	apply_check_pattern(t_rt *rt, float scale, int cur_obj, t_color oc)
{
	t_bool	resx;
	t_bool	resy;

	resx = FALSE;
	resy = FALSE;
	if(rt->object[cur_obj].type == PLANE)
		scale = 1.0f;
	if(((rt->uv_u * scale) - floorf(rt->uv_u * scale)) < 0.5f)
		resx = TRUE;
	if(((rt->uv_v * scale) - floorf(rt->uv_v * scale)) < 0.5f)
		resy = TRUE;
	if(resy ^ resx)
		return (col_lerp(oc, (t_color){0, 0, 0}, 0.5f));
	else
		return (oc);
		//	return (col_lerp(oc, (t_color){1, 1, 1}, 0.5f));
	
}

/*
*	Were translating a Cartesian coordinate into spherical coordinate into an
*	unique UV point.
*	[hp] is assumed to be a point in the surface of the sphere.
*	[n] is unit vector from [hp] to the sphere's origin point [pos].
*	to define unique set of spherical coordinates (r, θ, φ), they are restricted
*	to ranges of (180° or π rad) and (360° or 2π rad).
*	Additionally, due to spherical map being in 1:2 ratio, V is divided by 2.
*/
static void	spherical_map(t_rt *rt, t_fvector hp, t_fvector pos)
{
	t_fvector	n;

	n = v_normalize(v_sub(hp, pos));
	rt->uv_u = 0.5f + (atan2f(n.z, n.x) / (2.0f * M_PI));
	rt->uv_v = 0.5f + (asinf(n.y) / M_PI);
	rt->uv_v *= 0.5;
}

static void	planar_map(t_rt *rt, t_fvector hp)
{
	rt->uv_u = fmodf(hp.x, 1.0f);
	rt->uv_v = fmodf(hp.z, 1.0f);
}

static void	cylindrical_map(t_rt *rt, t_fvector pos)
{
	float	theta;

	theta = atan2f(pos.x, pos.z);
	rt->uv_u = 1.0f - (theta / (2.0f * M_PI) + 0.5f);
	rt->uv_v = fmodf(pos.y, (2 * M_PI)) * 1 / (2 * M_PI);
}

void	uv_map(t_rt *rt, t_ray *ray, int cur_obj)
{
	if (rt->object[cur_obj].type == SPHERE)
		spherical_map(rt, ray->start, rt->object[cur_obj].pos);
	if (rt->object[cur_obj].type == PLANE)
		planar_map(rt, ray->start);
	if (rt->object[cur_obj].type == CYL)
		cylindrical_map(rt, ray->start);
}
