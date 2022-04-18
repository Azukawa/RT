/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ales_rayc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:00:01 by esukava           #+#    #+#             */
/*   Updated: 2022/04/15 22:37:40 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_fvector	find_object_normal(t_object *o, t_ray *ray)
{
	t_fvector	n;
	float		t;

	n = (t_fvector){0, 0, 0};
	if (o->type == SPHERE)
		n = v_sub(ray->start, o->pos);
	else if (o->type == PLANE)
		n = o->dir;
	else if (o->type == CONE)
	{
		n = v_sub(ray->start, o->pos);
		n = v_sub(o->dir, v_div(v_mult(n, v_dot(o->dir, n)), v_dot(n, n)));
	}
	else
	{
		t = v_dot(v_sub(ray->start, o->pos), v_normalize(o->dir));
		n = v_sub(ray->start, v_add(o->pos, v_mult(o->dir, t)));
	}
	if (v_dot(ray->dir, n) > 0)
		n = v_mult(n, -1);
	return (v_normalize(n));
}

void	iter_screen(t_rt *rt)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			raytracer(rt, x, y);
			x++;
		}
		y++;
	}
}

void	ales_rayc(t_rt *rt)
{
	iter_screen(rt);
	rt->redraw = FALSE;
}
