/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:20:56 by esukava           #+#    #+#             */
/*   Updated: 2022/10/13 19:55:06 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	apply_sqr_tex(t_rt *rt, float scale)
{
	unsigned int	t_w;
	unsigned int	t_h;
	unsigned int	tex_x;
	unsigned int	tex_y;

	t_w = rt->surf->w;
	t_h = rt->surf->h;
	scale = scale / 10;
	rt->uv_u = fmodf(rt->uv_u, scale) + scale;
	tex_x = fmodf(rt->uv_u / scale * t_w, t_w);
	rt->uv_v = fmodf(rt->uv_v, scale) + scale;
	tex_y = fmodf(rt->uv_v / scale * t_h, t_h);
	return (uint_to_col(((uint32_t *)rt->surf->pixels)[(tex_x + tex_y * t_w)]));
}

/*
*	Returns a color corresponding to a checkered pattern. [Scale] directly
*	corresponds to how many tiles are generated onto the plane.
*/
t_color	apply_check(t_rt *rt, float scale, t_color oc)
{
	t_bool	resx;
	t_bool	resy;

	resx = FALSE;
	resy = FALSE;
	if (rt->object[rt->curobj].type == CONE
		|| rt->object[rt->curobj].type == CYL || rt->object[rt->curobj].mirror)
		return (oc);
	if (rt->object[rt->curobj].type == PLANE)
		scale = scale / 25;
	if (((rt->uv_u * scale) - floorf(rt->uv_u * scale)) < 0.5f)
		resx = TRUE;
	if (((rt->uv_v * scale) - floorf(rt->uv_v * scale)) < 0.5f)
		resy = TRUE;
	if (resy ^ resx)
		return (col_lerp(oc, (t_color){0, 0, 0}, 0.5f));
	else
		return (oc);
}
