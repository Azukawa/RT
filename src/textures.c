/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:20:56 by alero             #+#    #+#             */
/*   Updated: 2022/10/12 14:03:53 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	apply_texture(t_rt *rt)
{
	float k = 3;
	t_color ret;
	unsigned int	t_w = rt->surf->w;
	unsigned int	t_h = rt->surf->h;

	float	clamped_u, shifted_u, clamped_v, shifted_v;
//	printf("t_w = %d\tt_h = %d\n", t_w, t_h);
//		exit(0);
//	rt->uv_u = fmodf(rt->uv_u, k / 2) + k / 2;
//	rt->uv_v = fmodf(rt->uv_v, k / 2) + k / 2;
//	unsigned int tex_x = fmodf(rt->uv_u, t_w);
//	unsigned int tex_y = fmodf(rt->uv_v, t_h);
//	unsigned int tex_x = rt->uv_u * (t_w / k);
//	unsigned int tex_y = rt->uv_v * (t_h / k);
	
//	printf("input_u: %f\n",rt->uv_u);
	clamped_u = fmodf(rt->uv_u, k / 2.0f);
//	printf("clamped_u: %f\n",rt->uv_u);
	shifted_u = clamped_u + (k / 2.0f);
//	printf("shifted_u: %f\n",rt->uv_u);
//	unsigned int tex_x = fmodf(shifted_u / (k / 2) * t_w, t_w); //toimii jotenkuten, neliö kuva
	unsigned int tex_x = fmodf(shifted_u * (t_w / k), t_w);
//	printf("tex_x: %d\n",tex_x);


	clamped_v = fmodf(rt->uv_v, k / 2.0f);
//	printf("input_v: %f\n",rt->uv_v);
	shifted_v = clamped_v + (k / 2.0f);
//	printf("clamped_v: %f\n",rt->uv_v);
//	unsigned int tex_y = fmodf(shifted_v / (k / 2) * t_h, t_h); //toimii jotenkuten, neliökuva
	unsigned int tex_y = fmodf(shifted_v * (t_h /k), t_h);
//	printf("tex_y: %d\n",tex_y);
//	exit(0);
//	unsigned int tex_x = rt->uv_u * t_w;//fmodf(rt->uv_u, t_w);
//	unsigned int tex_y = rt->uv_v * t_h;//fmodf(rt->uv_v, t_h);
static int timo;
//	if (timo > -1 && timo < 200)
	if(timo == 1)
	{
		printf("tex_x = %u\ttex_y = %u\t uv_u = %f\tuv_v = %f\n", tex_x, tex_y, rt->uv_u, rt->uv_v);
		printf("timo = %d\n", timo);
	}
	if(timo == 599)
	{
		printf("tex_x = %u\ttex_y = %u\t uv_u = %f\tuv_v = %f\n", tex_x, tex_y, rt->uv_u, rt->uv_v);
		printf("timo = %d\n", timo);
//		exit(0);
	}
	timo++;	
	if (tex_x >= t_w || tex_y >= t_h)
	{
		printf("tex_x = %d\ttex_y=%d\n", tex_x, tex_y);
		printf("input_u: %f\n",rt->uv_u);
		printf("clamped_u: %f\n",clamped_u);
		printf("shifted_u: %f\n",shifted_u);
		printf("tex_x: %d\n",tex_x);
		exit(0);
	}

	//	ret = uint_to_col(((uint32_t *)rt->surf->pixels)[(tex_x + tex_y * t_w) *4]);
	ret = uint_to_col(((uint32_t *)rt->surf->pixels)[(tex_x + tex_y * t_w)]);
	return(ret);
//	return((t_color){0,0,0});
}

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
	if (rt->object[rt->curobj].type == CONE || rt->object[rt->curobj].type == CYL || rt->object[rt->curobj].mirror)
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

static void	planar_map(t_rt *rt, t_fvector hp)
{
	t_fvector	n;
	t_fvector	e1;
	t_fvector	e2;
	
//	hp = v_normalize(hp);
//	printf("x= %f\ty = %f\tz = %f\n", hp.x, hp.y, hp.z);
//	exit(0);
	n = rt->object[rt->curobj].dir;
	e1 = v_normalize(v_cross(n, (t_fvector){0, -1, 0, 0}));
//	printf("nx= %f\tny = %f\tnz = %f\n", n.x, n.y, n.z);
//	e1 = v_normalize(v_cross(n, (t_fvector){0, 1, 0, 0}));
	e2 = v_normalize(v_cross(n, e1));
//	rt->uv_u = fabs(fmodf(v_dot(e1, hp), 1)); 
//	rt->uv_v = fabs(fmodf(v_dot(e2, hp), 1));
//	rt->uv_v = (fmodf(v_dot(e1, hp), 1) + 1) / 2.0f;
//	rt->uv_u = (fmodf(v_dot(e2, hp), 1) + 1) / 2.0f;

//	rt->uv_v = fmodf(v_dot(e1, hp), 1);
//	rt->uv_u = fmodf(v_dot(e2, hp), 1);
//	printf("%f\n", v_dot(e1, hp));
//	exit(0);
//	rt->uv_u = (v_dot(e1, hp) + 1) / 2.0f;
//	rt->uv_v = (v_dot(e2, hp) + 1) / 2.0f;

//	rt->uv_u = fabs(v_dot(e1, hp)); 
//	rt->uv_v = fabs(v_dot(e2, hp));
//	printf("ex= %f\tey = %f\tez = %f\n", e1.x, e1.y, e1.z);

	rt->uv_u = v_dot(e1, hp); //uv ei oo [0,1]
	rt->uv_v = v_dot(e2, hp);
//	printf("uv_u: %f\n",rt->uv_u);
//	exit(0);
}

static void	cylindrical_map(t_rt *rt, t_fvector pos)
{
	float	theta;
	t_fvector	n, dir;
	
	dir = rt->object[rt->curobj].dir;
//	dir = (t_fvector){RAD_TO_DEG * dir.x, RAD_TO_DEG * dir.y, RAD_TO_DEG * dir.z};
	pos = v_rot_xyz(pos, dir);
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
