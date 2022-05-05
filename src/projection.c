/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:53:54 by eniini            #+#    #+#             */
/*   Updated: 2022/04/25 11:30:02 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_ray	init_ray(t_alt_cam cam, float u, float v)
{
	t_ray	r;

	r.start = cam.pos;
	r.dir = cam.llc;
	r.dir = v_add(r.dir, v_mult(cam.h, u));
	r.dir = v_add(r.dir, v_mult(cam.v, v));
	r.dir = v_sub(r.dir, cam.pos);
	r.dir = v_normalize(r.dir);
	return (r);
}

static void	init_extend(t_alt_cam *cam, t_fvector camdir, float ar, float h)
{
	t_fvector	w;
	t_fvector	u;
	t_fvector	v;
	t_fvector	vup;

	vup = (t_fvector){0, 1, 0};
	w = v_normalize(camdir);
	if (w.x == 0 && w.y == -1 && w.z == 0)
		vup = (t_fvector){0, 0, -1};
	u = v_normalize(v_cross(vup, w));
	v = v_cross(w, u);
	cam->h = v_mult(u, ar * 2.0f * h);
	cam->v = v_mult(v, 2.0f * h);
	cam->llc = v_sub(cam->pos, v_div(cam->h, 2.0f));
	cam->llc = v_sub(cam->llc, v_div(cam->v, 2.0f));
	cam->llc = v_sub(cam->llc, w);
}

/*
*	This could be expanded to be more runtime-defineable.
*	Vector [llc] stands for "lower left corner", which points to the starting
*	point in the perspective projection 'screen' that raytracer moves through.
*/
void	init_alt_cam(t_alt_cam *cam, t_fvector lookfrom, t_fvector lookat)
{
	float		theta;
	float		h;
	float		vfov;
	float		ar;

	vfov = 45;
	ar = 4.0f / 3.0f;
	theta = vfov * DEG_TO_RAD;
	h = tanf(theta / 2.0f);
	cam->pos = lookfrom;
	cam->dir = lookat;
	init_extend(cam, v_sub(lookfrom, lookat), ar, h);
}
