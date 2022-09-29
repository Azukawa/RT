/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:41:45 by esukava           #+#    #+#             */
/*   Updated: 2022/09/29 19:02:30 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
*	[Ray] is the point of interception between ray & [rt->curobj].
*	If a point is not directly illuminated or is in a shadow of another object,
*	no new color is applied.
*
*	Note: rt->t exists to store length of the vector between interception point
*	and the predetermined light source. Without light falloff etc. its not used.
*/
static void	calculate_lighting(t_rt *rt, t_ray *ray, t_color *c)
{
	t_ray		lr;
	t_fvector	dist;
	t_fvector	n;

	n = find_object_normal(&rt->object[rt->curobj], ray);
	if (v_dot(n, ray->dir) > 0)
		n = v_mult(n, -1);
	dist = v_sub(rt->light[rt->cur_light].pos, ray->start);
	lr.start = v_add(ray->start, v_mult(n, 0.0001f));
	lr.dir = v_normalize(dist);
	if (in_shadow(rt, lr, dist))
		return ;
	*c = col_add(*c, assign_color(rt, lr, n, *c), 0.5f);
}

//this function is called if ray_prime hits mirror object.
//In such case ray_prime is re-initialized to shoot from the mirror object.
void	hit_mirror(t_rt *rt, float *t, unsigned int depth)
{
	unsigned int	i;
	t_fvector		n;

	i = 0;
	rt->r_prm.start = v_add(rt->r_prm.start, v_mult(rt->r_prm.dir, *t));
	n = find_object_normal(&rt->object[rt->curobj], &rt->r_prm);
	*t = RAY_LIMIT;
	rt->curobj = -1;
	rt->r_prm.dir = v_mult(v_mult(v_sub(rt->r_prm.dir, n), 2.0f), \
v_dot(rt->r_prm.dir, n));
	v_normalize(rt->r_prm.dir);
	while (i < rt->objcount)
	{	
		if (ray_object_intersect(&rt->r_prm, &rt->object[i], t))
			rt->curobj = i;
		i++;
	}
	if (rt->object[rt->curobj].mirror == 1 && depth > 0)
		hit_mirror(rt, t, depth--);
}

static t_color	ray_col(t_rt *rt, float t)
{
	t_color		mixer;

	rt->cur_light = 0;
	rt->r_lght.start = v_add(rt->r_prm.start, \
		v_mult(rt->r_prm.dir, t));
	rt->r_lght.dir = rt->r_prm.dir;
	uv_map(rt, &rt->r_lght);
	mixer = col_multiply(rt->object[rt->curobj].color, rt->amb_int);
	while (rt->cur_light < rt->light_count)
	{
		calculate_lighting(rt, &rt->r_lght, &mixer);
		rt->cur_light++;
	}
	mixer = col_blend(mixer, apply_check_pattern(rt, 25, mixer), 0.7f);
	return (mixer);
}

void	raytracer(t_rt *rt, int x, int y)
{
	unsigned int	i;
	float			t;

	ray_trough_screen(rt, x, y);
	t = RAY_LIMIT;
	rt->curobj = -1;
	i = 0;
	while (i < rt->objcount)
	{
		if (ray_object_intersect(&rt->r_prm, &rt->object[i], &t))
			rt->curobj = i;
		i++;
	}
	if (rt->object[rt->curobj].mirror == 1)
		hit_mirror(rt, &t, 5);
	if (draw_light(rt, &t, x, y) || rt->curobj == -1)
		return ;
	if (rt->is_grayscale)
		draw_pixel(x, y, &rt->rend.win_buffer, \
			convert_to_grayscale(col_to_uint(ray_col(rt, t))));
	else
		draw_pixel(x, y, &rt->rend.win_buffer, \
col_to_uint(ray_col(rt, t)));
}
