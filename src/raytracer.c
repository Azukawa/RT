/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:41:45 by esukava           #+#    #+#             */
/*   Updated: 2022/05/09 16:21:59 by eniini           ###   ########.fr       */
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
*	Returns a vector representing the relfection direction given the
*	incident (ray hitting a surface coming from a light source) [I] and surface
*	normal [N] vectors.
*	I - (2 * dot(N, I) * N).
*/
static t_fvector	reflect(t_fvector incident, t_fvector normal)
{
	float	difference;

	difference = 2.0f * v_dot(normal, incident);
	return (v_sub(v_mult(normal, difference), incident));
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
	uv_map(rt, ray, cur_obj);
	//mat.diffuse = apply_texture(rt, rt->uv_u, rt->uv_v); //insane procedural texture creation
	mat.diffuse = col_lerp(mat.diffuse, apply_check_pattern(rt, 5, rt->object[cur_obj]), 0.5f);
	mat.diffuse = col_lerp(mat.diffuse, rt->amb_l, rt->amb_p);	//mix ambient light in depending on its intensity
	*color = assign_color(rt, lr, n, mat); //v_dot(lr.dir, n), mat);
}

void	raytracer(t_rt *rt, int x, int y)
{
	int			i;
	t_color		mixer;
	uint32_t	color;
	float		t;
	int			cur_obj;

	color = 0;
	//rt->ray_prime = init_ray(rt->altcam, (float)x / (WIN_W - 1), (float)y / WIN_H - 1);
	ray_trough_screen(rt, x, y);
	t = 20000.0f;
	cur_obj = -1;
	i = 0;
	while (i < rt->object_count)
	{
		if (ray_object_intersect(&rt->ray_prime, &rt->object[i], &t))
			cur_obj = i;
		mixer = col_multiply(rt->material[rt->object[cur_obj].material].diffuse, rt->amb_p);
		color = col_to_uint(col_blend(mixer, rt->amb_l, rt->amb_p));
		rt->light[0].amb_col = col_blend(mixer, rt->amb_l, rt->amb_p);
		i++;
	}
	if (draw_light(rt, &t, x, y))
		return ;		//hit debug lightpoint, end casting
	//if (draw_debug_cam(rt, &t, x, y))
	//	return ;
	if (cur_obj == -1)
		return ;		//no objects found, stay black
	rt->ray_light.start = v_add(rt->ray_prime.start, v_mult(rt->ray_prime.dir, t));
	rt->ray_light.dir = rt->ray_prime.dir;
	calculate_lighting(rt, &rt->ray_light, cur_obj, &color);
	if (rt->keys.is_grayscale)
		color = convert_to_grayscale(color);
	draw_pixel(x, y, &rt->rend.win_buffer, color);
}
