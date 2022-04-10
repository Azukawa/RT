/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:02:27 by esukava           #+#    #+#             */
/*   Updated: 2022/04/10 18:37:24 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	init_material(t_rt *rt)
{
	rt->material[0].diffuse.red = 1;
	rt->material[0].diffuse.green = 0;
	rt->material[0].diffuse.blue = 0;
	rt->material[0].reflection = 1;
	rt->material[1].diffuse.red = 0.7;
	rt->material[1].diffuse.green = 0.7;
	rt->material[1].diffuse.blue = 0.7;
	rt->material[1].reflection = 1;
	rt->material[2].diffuse.red = 0;
	rt->material[2].diffuse.green = 0;
	rt->material[2].diffuse.blue = 1;
	rt->material[2].reflection = 1;
}

void	init_light(t_rt *rt)
{
	rt->object[9].r = 1;
	rt->object[9].type = LIGHT;
	rt->object[9].intensity.red = 1;
	rt->object[9].intensity.green = 1;
	rt->object[9].intensity.blue = 1;
	rt->light[0].pos.x = 0;
	rt->light[0].pos.y = 0;
	rt->light[0].pos.z = 0;
	rt->light[0].intensity.red = 0.1;
	rt->light[0].intensity.green = 0.1;
	rt->light[0].intensity.blue = 0.1;
	rt->light[0].amb_int = 0.2;
	rt->amb_l = (t_color){0, 25 / 255.f, 50 / 255.f}; //DEBUG COLOR (t_color){83 / 255.f, 227 / 255.f, 106 / 255.f};
	rt->amb_p = 0.5f;
}

void	init_player(t_rt *rt)
{
	rt->sx = 0;
	rt->sy = 0;
	rt->cam.pos.x = 0;
	rt->cam.pos.y = 0;
	rt->cam.pos.z = -50;
	rt->cam.rot.x = 0;
	rt->cam.rot.y = 0;
	rt->cam.rot.z = 0;
	rt->object_count = 2;
	rt->redraw = TRUE;
	rt->cam.up = v_normalize(v_cross(rt->cam.right, rt->cam.front));
}

void	init(t_rt *rt)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit(1);
	rt->rend.win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!rt->rend.win)
		exit(1);
	rt->rend.renderer = SDL_CreateRenderer(rt->rend.win, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!rt->rend.renderer)
		exit(1);
	rt->rend.win_tex = SDL_CreateTexture(rt->rend.renderer, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!rt->rend.win_tex)
		exit(1);
	rt->rend.run = TRUE;
	init_material(rt);
	init_light(rt);
	init_player(rt);
}
