/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:42 by eniini            #+#    #+#             */
/*   Updated: 2022/05/06 10:49:06 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
*	Returns a color corresponding to a checkered pattern. [Scale] directly
*	corresponds to how many tiles are generated onto the plane.
*
*	Note: scales higher than 1 don't work with planar mapping.
*/
t_color	apply_check_pattern(t_rt *rt, float scale, float x, float y)
{
	t_bool	yresult;
	t_bool	xresult;
	t_bool	result;

	//y *= 0.5f;
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

/*
*	TESTING
*/
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
static void	spherical_map(t_rt *rt, t_fvector pos, t_fvector hp, t_object obj)
{
	float	theta;
	float	phi;
	float	raw_u;

	theta = atan2f(pos.x, pos.z);
	rt->uv_u = 1.0f - (theta / (2.0f * M_PI) + 0.5f);
	phi = acosf(pos.y / v_len(v_sub(hp, obj.pos)));
	rt->uv_v = 1.0f - (phi / M_PI);
	rt->uv_v *= 0.5;
}

static void planar_map(t_rt *rt, t_fvector hp)
{
	rt->uv_u = fmodf(hp.x, 1.0f);
	rt->uv_v = fmodf(hp.z, 1.0f);
}

static void	cylindrical_map(t_rt *rt, t_fvector pos)
{
	float	theta;
	float	phi;
	float	raw_u;

	theta = atan2f(pos.x, pos.z);
	//phi = acosf(pos.y / v_len(v_sub(hp, obj.pos)));
	rt->uv_u = 1.0f - (theta / (2.0f * M_PI) + 0.5f);
	//rt->uv_v = 1.0f - (phi / M_PI);
	rt->uv_v = fmodf(pos.y, (2 * M_PI)) * 1 / (2 * M_PI);
	rt->uv_v *= 0.2;
}

void	uv_map(t_rt *rt, t_ray *ray, int cur_obj)
{
	if (rt->object[cur_obj].type == SPHERE)
	{
		spherical_map(rt, ray->start, ray->start, rt->object[cur_obj]);
	}
	if (rt->object[cur_obj].type == PLANE)
	{
		planar_map(rt, ray->start);
	}
	if (rt->object[cur_obj].type == CYL)
	{
		cylindrical_map(rt, ray->start);
	}
}
