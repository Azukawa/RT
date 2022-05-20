/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:13:52 by esukava           #+#    #+#             */
/*   Updated: 2022/05/20 13:10:52 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ray_trough_screen(t_rt *rt, int x, int y)
{
	t_ray		ret;
	t_fvector	pixel;

	ret.start = rt->cam.pos;
	pixel.x = lerp1d(-1.0, 1.0, (1.0f / WIN_W) * (x + 0.5));
	pixel.y = lerp1d(-0.75, 0.75, (1.0f / WIN_H) * (y + 0.5));
	pixel.z = 1;
	pixel = v_rot_xyz(pixel, rt->cam.rot);
	ret.dir = v_normalize(pixel);
	rt->ray_prime = ret;
}

t_bool	ray_object_intersect(t_ray *ray, t_object *obj, float *t)
{
	if (obj->type == SPHERE)
		return (ray_sphere_intersect(ray, obj, t));
	else if (obj->type == PLANE)
		return (ray_plane_intersect(ray, obj, t));
	else if (obj->type == CYL)
		return (ray_cyl_intersect(ray, obj, t));
	else if (obj->type == CONE)
		return (ray_cone_intersect(ray, obj, t));
	return (FALSE);
}

t_bool	draw_light(t_rt *rt, float *t, int x, int y)
{
	if (ray_sphere_intersect(&rt->ray_prime, &rt->object[9], t))
	{
		draw_pixel(x, y, &rt->rend.win_buffer, 0xFFFF00);
		return (TRUE);
	}
	return (FALSE);
}
