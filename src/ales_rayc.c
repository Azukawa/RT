/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ales_rayc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:00:01 by esukava           #+#    #+#             */
/*   Updated: 2022/04/10 18:37:41 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	cone_normal(t_fvector new_start, t_object *object, t_fvector *n)
{
	*n = v_sub(new_start, object->pos);
	*n = v_div(v_mult(*n, v_dot(object->dir, *n)), v_dot(*n, *n));
	*n = v_sub(object->dir, *n);
}

t_fvector	find_object_normal(t_object *object, t_ray *ray)
{
	t_fvector	n;
	t_fvector	pt;
	t_fvector	temp;
	float		t;

	n = (t_fvector){0, 0, 0};
	if (object->type == SPHERE)
		n = v_sub(ray->start, object->pos);
	else if (object->type == PLANE)
		n = object->dir;
	else if (object->type == CONE)
		cone_normal(ray->start, object, &n);
	else
	{
		temp = v_sub(ray->start, object->pos);
		t = v_dot(temp, v_normalize(object->dir));
		pt = v_add(object->pos, v_mult(object->dir, t));
		n = v_sub(ray->start, pt);
	}
	if (v_dot(ray->dir, n) > 0)
		n = v_mult(n, -1);
	return (v_normalize(n));
}

void	iter_screen(t_rt *rt)
{
	rt->sx = 0;
	rt->sy = 0;
	while (rt->sy < WIN_H)
	{
		while (rt->sx < WIN_W)
		{
			raytracer(rt, 0);
			rt->sx++;
		}
		rt->sy++;
		rt->sx = 0;
	}
}

void	ales_rayc(t_rt *rt)
{
	iter_screen(rt);
	rt->redraw = FALSE;
}
