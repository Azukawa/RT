/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:37:54 by eniini            #+#    #+#             */
/*   Updated: 2022/06/11 17:06:38 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_sphere(t_object *obj, t_fvector orig, float radius, t_color c)
{
	obj->type = SPHERE;
	obj->pos = orig;
	obj->dir = orig;
	obj->r = radius;
	obj->color = c;
}

void	init_plane(t_object *obj, t_fvector orig, t_fvector dir, t_color c)
{
	obj->type = PLANE;
	obj->pos = orig;
	obj->dir = dir;
	obj->r = 0.0f;
	obj->color = c;
}

/*
*	Note: cylinder's radius is given as the [dir.w].
*/
void	init_cyl(t_object *obj, t_fvector orig, t_fvector dir, t_color c)
{
	t_fvector	v;

	obj->type = CYL;
	obj->pos = orig;
	obj->r = dir.w;
	v = (t_fvector){dir.x, dir.y, dir.z, 1};
	obj->dir = v;
	obj->color = c;
}

/*
*	Note: cone's radius is given as [dir.w].
*/
void	init_cone(t_object *obj, t_fvector orig, t_fvector dir, t_color c)
{
	t_fvector	v;

	obj->type = CONE;
	obj->pos = orig;
	obj->angle = dir.w;
	v = (t_fvector){dir.x, dir.y, dir.z, 1};
	obj->r = 0;
	obj->dir = v;
	obj->color = c;
}
