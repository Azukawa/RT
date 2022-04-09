/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:41:45 by esukava           #+#    #+#             */
/*   Updated: 2022/04/09 12:33:14 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_bool	in_shadow(t_rt *rt, t_ray light_ray, t_fvector n,
int cur_obj)
{
	int		k;

	k = 0;
	while (k < rt->object_count)
	{
		if (v_dot(n, light_ray.dir) > 0 && k != cur_obj
			&& ray_object_intersect(&light_ray, &rt->object[k], &rt->t))
			return (TRUE);
		k++;
	}
	return (FALSE);
}

/*
*	[Mat] is the current object material data.
*	[lambert] is the dot product angle between current object and given light.
*/
static uint32_t	assign_color(t_rt *rt, float lambert, t_material mat)
{
	/*
	t_fvector	col;

	col.x = lambert * rt->object[9].intensity.red * mat.diffuse.red;
	col.y = lambert * rt->object[9].intensity.green * mat.diffuse.green;
	col.z = lambert * rt->object[9].intensity.blue * mat.diffuse.blue;
	col.x = fmax(col.x, rt->light[0].amb_col.red);
	col.y = fmax(col.y, rt->light[0].amb_col.green);
	col.z = fmax(col.z, rt->light[0].amb_col.blue);
	return (get_color2(ft_fmin(col.x * 255.0f, 255.0f), ft_fmin(col.y * 255.0f, 255.0f), ft_fmin(col.z * 255.0f, 255.0f)));
	*/
	return (col_to_uint(col_blend(col_multiply(rt->amb_l, rt->amb_p), mat.diffuse, lambert)));
}

/*
*	[Ray] is the point of interception between ray & [cur_obj].
*	If a point is not directly illuminated or is in a shadow of another object,
*	no new color is applied.
*
*	Note: rt->t exists to store length of the vector between interception point
*	and the predetermined light source. Without light falloff etc. its not used.
*/
static void	calculate_lighting(t_rt *rt, t_ray *ray, int cur_obj,
uint32_t *color)
{
	t_ray		lr;
	//float		t1;
	t_fvector	dist;
	t_material	mat;
	t_fvector	n;

	n = find_object_normal(&rt->object[cur_obj], ray);
	if (v_dot(n, ray->dir) > 0)
		v_mult(n, -1);
	dist = v_sub(rt->object[9].pos, ray->start);	//distance of light
	if (v_dot(n, dist) <= 0)						//not facing the light
		return ;
	lr.start = v_add(ray->start, v_mult(n, 0.05));
	lr.dir = v_normalize(dist);
	if (in_shadow(rt, lr, n, cur_obj))
		return ;
	mat = rt->material[rt->object[cur_obj].material];			//local copy of a preset material
	mat.diffuse = col_lerp(mat.diffuse, rt->amb_l, rt->amb_p);	//mix ambient light in depending on its intensity
	*color = assign_color(rt, v_dot(lr.dir, n), mat);
}

void	raytracer(t_rt *rt, int i)
{
	t_ray		ray;
	uint32_t	color;
	float		t;
	int			cur_obj;

	color = 0;
	ray = ray_trough_screen(rt);
	t = 20000.0f;
	cur_obj = -1;
	i = 0;
	while (i < rt->object_count)
	{
		if (ray_object_intersect(&ray, &rt->object[i], &t))
			cur_obj = i;
		color = col_to_uint(col_multiply(rt->amb_l, rt->amb_p));	//Init object color to ambient light = not illuminated by any light source
		//color = assign_color(rt,  rt->light[0].amb_int, rt->material[rt->object[cur_obj].material]);
		rt->light[0].amb_col.red = rt->material[rt->object[cur_obj].material].diffuse.red * rt->light[0].amb_int;
		rt->light[0].amb_col.green = rt->material[rt->object[cur_obj].material].diffuse.green * rt->light[0].amb_int;
		rt->light[0].amb_col.blue = rt->material[rt->object[cur_obj].material].diffuse.blue * rt->light[0].amb_int;
		i++;
	}
	if (draw_light(&ray, rt, &t))
		return ;		//hit debug lightpoint, end casting
	if (cur_obj == -1)
		return ;		//no objects found, stay black
	ray.start = v_add(ray.start, v_mult(ray.dir, t));
	calculate_lighting(rt, &ray, cur_obj, &color);
	if (rt->keys.is_grayscale)
		color = convert_to_grayscale(color);
	draw_pixel(rt->sx, rt->sy, &rt->rend.win_buffer, color);
}
