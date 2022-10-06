/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:20:56 by alero             #+#    #+#             */
/*   Updated: 2022/10/06 16:09:18 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
*	Returns a color corresponding to a checkered pattern. [Scale] directly
*	corresponds to how many tiles are generated onto the plane.
*/
t_color	apply_check_pattern(t_rt *rt, float scale, t_color oc)
{
	t_bool	resx;
	t_bool	resy;

	resx = FALSE;
	resy = FALSE;
	if (rt->object[rt->curobj].type == CONE)
		return (oc);
	if (rt->object[rt->curobj].type == PLANE)
		scale = scale / 25;
	if (((rt->uv_u * scale) - floorf(rt->uv_u * scale)) < 0.5f)
		resx = TRUE;
	if (((rt->uv_v * scale) - floorf(rt->uv_v * scale)) < 0.5f)
		resy = TRUE;
	if (resy ^ resx)
		return (col_lerp(oc, (t_color){0, 0, 0}, 0.5f));
	else
		return (oc);
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
/*
t_fvector	v_multiply(t_fvector a, t_fvector b)
{
t_vec	m3_multiply_vec(t_m3 m, t_vec v)
{
	t_vec	ret;

	ret.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2];
	ret.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2];
	ret.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2];
	return (ret);
}
}
*/
static void	planar_map(t_rt *rt, t_fvector hp)
{
	t_fvector n;
	static int bing;
	t_fvector	e1, e2;
	n = rt->object[rt->curobj].dir;
	if(bing == 100)
	{
		printf("n.x = %f\tn.y = %f\tn.z = %f\n", n.x, n.y, n.z);
		printf("hp.x = %f\thp.y = %f\thp.z = %f\n", hp.x, hp.y, hp.z);
	}
//	n = v_sub(n, (t_fvector){0, 1, 0});
//	n = (t_fvector){RAD_TO_DEG * n.x, RAD_TO_DEG * n.y, RAD_TO_DEG * n.z};
//	n = v_rot_xyz(hp, n);
	e1 = v_normalize(v_cross(n, (t_fvector){1, 0, 0}));
	e2 = v_normalize(v_cross(n, e1));
//	if(bing == 100)
//		printf("n.x = %f\tn.y = %f\tn.z = %f\n", n.x, n.y, n.z);
//	rt->uv_u = fmodf(n.x, 1.0f); //og
//	rt->uv_v = fmodf(n.z, 1.0f); //og



	rt->uv_u = v_dot(e1, hp); 
	rt->uv_v = v_dot(e2, hp);
//	if(bing == 100){
//		printf("cam posx = %f\tray_startx = %f\n", rt->cam.pos.x, rt->r_prm.start.x);
//		printf("cam posy = %f\tray_starty = %f\n", rt->cam.pos.y, rt->r_prm.start.y);
//	}
//	rt->uv_u = rt->cam.pos.x + rt->r_prm.dir.x * iso_t;
//	rt->uv_v = rt->cam.pos.y + rt->r_prm.dir.y * iso_t;


	bing++;
}

static void	cylindrical_map(t_rt *rt, t_fvector pos)
{
	float	theta;

	theta = atan2f(pos.x, pos.z);
	rt->uv_u = 1.0f - (theta / (2.0f * M_PI) + 0.5f);
	rt->uv_v = fmodf(pos.y, (2 * M_PI)) * 1 / (2 * M_PI);
}

void	uv_map(t_rt *rt, t_ray *ray)
{
	if (rt->object[rt->curobj].type == SPHERE)
		spherical_map(rt, ray->start, rt->object[rt->curobj].pos);
	if (rt->object[rt->curobj].type == PLANE)
		planar_map(rt, ray->start);
	if (rt->object[rt->curobj].type == CYL)
		cylindrical_map(rt, ray->start);
}
