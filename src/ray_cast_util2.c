/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:53:44 by esukava           #+#    #+#             */
/*   Updated: 2022/10/07 13:08:30 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bool	in_shadow(t_rt *rt, t_ray light_ray, t_fvector dist)
{
	int	i;

	i = 0;
	while (i < (int)rt->objcount)
	{
		rt->t = RAY_LIMIT;
		if ((ray_object_intersect(&light_ray, \
&rt->object[i], &rt->t)) && v_len(dist) > rt->t)
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
	mix = col_add(mix, col_mult_colors(rt->object[rt->curobj].color,
				rt->light[rt->cur_light].color), (lambert /** 0.8*/));
	final = col_add(mix, col_mult_colors(rt->light[rt->cur_light].color,
				rt->object[rt->curobj].color), phong);
	return (final);
}
