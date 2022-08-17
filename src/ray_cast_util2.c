/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:53:44 by alero             #+#    #+#             */
/*   Updated: 2022/08/17 14:57:55 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bool	in_shadow(t_rt *rt, t_ray light_ray, unsigned int cur_obj, \
t_fvector dist)
{
	unsigned int	i;

	i = 0;
	while (i < rt->objcount)
	{
		rt->t = v_len(v_sub(light_ray.start, rt->object[i].pos));
		if (i != cur_obj && (ray_object_intersect(&light_ray, &rt->object[i], \
&rt->t)) && v_len(dist) > rt->t)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
*	[Mat] is the current object material data.
*	[lray] holds the direction of light and the hit point in question.
*	[n] is the given object surface normal.
*/
t_color	assign_color(t_rt *rt, t_ray lray, t_fvector n, t_color mix)
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
