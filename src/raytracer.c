/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:41:45 by esukava           #+#    #+#             */
/*   Updated: 2022/04/13 16:46:59 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

#define DEBUG_ROUGHNESS 120.f

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
*	Explanation taken from Khronos.org:
*	For a given incident vector [I] and surface normal [N] reflect returns the
*	reflection direction calculated as I - 2.0 * dot(N, I) * N.
*	N should be normalized in order to achieve the desired result.
*/
static t_fvector	reflect(t_fvector vec_from_light, t_fvector normal)
{
	return (v_sub(v_mult(vec_from_light, 2.0f * v_dot(normal, vec_from_light)), vec_from_light));
	//return (v_sub(vec_from_light, v_mult(v_mult(normal,
	//			v_dot(normal, vec_from_light)), 2.0f)));
}

/*
*	[Mat] is the current object material data.
*	[lray] holds the direction of light and the hit point in question.
*	[n] is the given object surface normal.
*/
static uint32_t	assign_color(t_rt *rt, t_ray lray, t_fvector n, t_material mat)
{
	float	phong;
	float	lambert;
	t_color	ambient;
	t_color	specular;
	t_color	final;

	phong = fmaxf(v_dot(reflect(lray.dir, n), v_normalize(rt->cam.pos)), 0.0f);
	phong = powf(ft_clamp_f(phong, 0.0f, 1.0f), DEBUG_ROUGHNESS);
	lambert = v_dot(lray.dir, n);
	ambient = col_multiply(rt->amb_l, rt->amb_p);
	specular = col_multiply((t_color){1,1,1}, phong); //debugging with pure white light
	final = col_add(rt->light[0].amb_col, mat.diffuse, lambert);
	final = col_add(final, specular, 1.0f);
	return (col_to_uint(final));
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
	*color = assign_color(rt, lr, n, mat); //v_dot(lr.dir, n), mat);
}

void	raytracer(t_rt *rt, int i)
{
	t_ray		ray;
	t_color		mixer;
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
		mixer = col_multiply(rt->material[rt->object[cur_obj].material].diffuse, rt->amb_p);
		color = col_to_uint(col_blend(mixer, rt->amb_l, rt->amb_p));
		rt->light[0].amb_col = col_blend(mixer, rt->amb_l, rt->amb_p);
		//color = col_to_uint(col_blend(rt->material[rt->object[cur_obj].material].diffuse, rt->amb_l, rt->amb_p));	//Init object color to ambient light = not illuminated by any light source
		//color = assign_color(rt,  rt->light[0].amb_int, rt->material[rt->object[cur_obj].material]);
		//rt->light[0].amb_col.red = rt->material[rt->object[cur_obj].material].diffuse.red * rt->light[0].amb_int;
		//rt->light[0].amb_col.green = rt->material[rt->object[cur_obj].material].diffuse.green * rt->light[0].amb_int;
		//rt->light[0].amb_col.blue = rt->material[rt->object[cur_obj].material].diffuse.blue * rt->light[0].amb_int;
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
