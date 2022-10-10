/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:20:56 by alero             #+#    #+#             */
/*   Updated: 2022/10/10 16:54:42 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	apply_texture(t_rt *rt)
{
	float scale = 40;
//	printf("pixeltype = %d\n", SDL_PIXELTYPE(rt->surf->format->format));
//	printf("pixelORDER = %d\n", SDL_PIXELORDER(rt->surf->format->format));
//	printf("pixelayout = %d\n", SDL_PIXELLAYOUT(rt->surf->format->format));
	t_color ret;
	unsigned int	t_w = rt->surf->w;
	unsigned int	t_h = rt->surf->h;
	unsigned int tex_x = fmodf(rt->uv_u * scale, t_w);
	unsigned int tex_y = fmodf(rt->uv_v * scale, t_h);
	
//	unsigned int tex_x = rt->uv_u * t_w;//fmodf(rt->uv_u, t_w);
//	unsigned int tex_y = rt->uv_v * t_h;//fmodf(rt->uv_v, t_h);
//static int timo;
//	if (timo > -1 && timo < 200)
//		printf("tex_x = %d\ttex_y = %d\t uv_u = %f\tuv_v = %f\n", tex_x, tex_y, rt->uv_u, rt->uv_v);
//	timo++;	
//	ret = uint_to_col(((uint32_t *)rt->surf->pixels)[(tex_x + tex_y * t_w) *4]);
	ret = uint_to_col(((uint32_t *)rt->surf->pixels)[(tex_x + tex_y * t_w)]);
	return(ret);
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

	n = rt->object[rt->curobj].dir;
	e1 = v_normalize(v_cross(n, (t_fvector){1, 0, 0, 0}));
	e2 = v_normalize(v_cross(n, e1));
//	rt->uv_u = fabs(fmodf(v_dot(e1, hp), 1)); 
//	rt->uv_v = fabs(fmodf(v_dot(e2, hp), 1));
	rt->uv_u = fabs(v_dot(e1, hp)); 
	rt->uv_v = fabs(v_dot(e2, hp));

//	rt->uv_u = v_dot(e1, hp); 
//	rt->uv_v = v_dot(e2, hp);
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
