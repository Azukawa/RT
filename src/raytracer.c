/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:41:45 by esukava           #+#    #+#             */
/*   Updated: 2022/06/08 00:32:02 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bool	in_shadow(t_rt *rt, t_ray light_ray, uint cur_obj)
{
	uint	i;

	i = 0;
	while (i < rt->objcount && i != cur_obj)
	{
		rt->t = v_len(v_sub(light_ray.start, rt->object[i].pos));
		rt->t = RAY_LIMIT;
		if (ray_object_intersect(&light_ray, &rt->object[i], &rt->t))
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/*
*	Returns a vector representing the relfection direction given the
*	incident (ray hitting a surface coming from a light source) [I] and surface
*	normal [N] vectors.
*	I - (2 * dot(N, I) * N).
static t_fvector	reflect(t_fvector incident, t_fvector normal)
{
	float	difference;

	difference = 2.0f * v_dot(normal, incident);
	return (v_sub(v_mult(normal, difference), incident));
}*/

/*
*	[Mat] is the current object material data.
*	[lray] holds the direction of light and the hit point in question.
*	[n] is the given object surface normal.
*/
static t_color	assign_color(t_rt *rt, t_ray lray, t_fvector n, t_color mix)
{
	float	phong;
	float	lambert;
	float	difference;
	t_color	final;

	difference = 2.0f * v_dot(n, lray.dir);
	phong = fmaxf(v_dot(v_sub(v_mult(n, difference), lray.dir), \
			v_normalize(rt->cam.pos)), 0.0f);
	phong = powf(ft_clamp_d(phong, 0.0f, 1.0f), ROUGHNESS);
	lambert = v_dot(lray.dir, n);
	mix = col_blend(mix, rt->light.color, (lambert * 0.8));
	final = col_add(mix, col_multiply((t_color){1, 1, 1}, phong), phong);
	return (final);
}

/*
*	[Ray] is the point of interception between ray & [cur_obj].
*	If a point is not directly illuminated or is in a shadow of another object,
*	no new color is applied.
*
*	Note: rt->t exists to store length of the vector between interception point
*	and the predetermined light source. Without light falloff etc. its not used.
*/
static void	calculate_lighting(t_rt *rt, t_ray *ray, int cur_obj, t_color *c)
{
	t_ray		lr;
	t_fvector	dist;
	t_fvector	n;

	n = find_object_normal(&rt->object[cur_obj], ray);
	if (v_dot(n, ray->dir) > 0)
		v_mult(n, -1);
	dist = v_sub(rt->light.pos, ray->start);
	if (v_dot(n, dist) <= 0)
		return ;
	lr.start = v_add(ray->start, v_mult(n, 0.0001f));
	lr.dir = v_normalize(dist);
	if (in_shadow(rt, lr, cur_obj))
	{
		*c = col_multiply(*c, 0.2f);
		return ;
	}
	*c = assign_color(rt, lr, n, *c);
}

static t_color	ray_col(t_rt *rt, int cur_obj, float t)
{
	t_color		mixer;

	rt->ray_light.start = v_add(rt->ray_prime.start, \
		v_mult(rt->ray_prime.dir, t));
	rt->ray_light.dir = rt->ray_prime.dir;
	uv_map(rt, &rt->ray_light, cur_obj);
	mixer = col_add(rt->object[cur_obj].color, rt->amb_col, 1.0f);
	calculate_lighting(rt, &rt->ray_light, cur_obj, &mixer);
	mixer = col_blend(mixer, apply_check_pattern(rt, 25, cur_obj, mixer), 0.1f);
	return (mixer);
}

void	raytracer(t_rt *rt, int x, int y)
{
	uint		i;
	float		t;
	t_bool		hit;

	ray_trough_screen(rt, x, y);
	t = RAY_LIMIT;
	hit = FALSE;
	i = 0;
	while (i < rt->objcount && !hit)
	{
		if (ray_object_intersect(&rt->ray_prime, &rt->object[i], &t))
		{
			hit = TRUE;
			break ;
		}
		i++;
	}
	if (draw_light(rt, &t, x, y) || !hit)
		return ;
	if (rt->is_grayscale)
		draw_pixel(x, y, &rt->rend.win_buffer, \
			convert_to_grayscale(col_to_uint(ray_col(rt, i, t))));
	else
		draw_pixel(x, y, &rt->rend.win_buffer, col_to_uint(ray_col(rt, i, t)));
}
