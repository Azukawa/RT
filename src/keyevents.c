/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:37 by esukava           #+#    #+#             */
/*   Updated: 2022/09/23 19:48:08 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_keyevents(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_d)
		rt->light.pos.z += 5;
	if (e->key.keysym.sym == SDLK_w)
		rt->light.pos.x -= 5;
	if (e->key.keysym.sym == SDLK_a)
		rt->light.pos.z -= 5;
	if (e->key.keysym.sym == SDLK_s)
		rt->light.pos.x += 5;
	if (e->key.keysym.sym == SDLK_q)
		rt->light.pos.y += 5;
	if (e->key.keysym.sym == SDLK_e)
		rt->light.pos.y -= 5;
	if (e->key.keysym.sym == SDLK_g && rt->is_grayscale)
		rt->is_grayscale = FALSE;
	else if (e->key.keysym.sym == SDLK_g && !rt->is_grayscale)
		rt->is_grayscale = TRUE;
	if (e->key.keysym.sym == SDLK_m && rt->amb_p < AMBIENT_MAX)
		rt->amb_p += 0.05f;
	if (e->key.keysym.sym == SDLK_n && rt->amb_p > AMBIENT_MIN)
		rt->amb_p -= 0.05f;
	if (e->key.keysym.sym == SDLK_v && rt->amb_int < AMBIENT_MAX)
		rt->amb_int += 0.05f;
	if (e->key.keysym.sym == SDLK_b && rt->amb_int > AMBIENT_MIN)
		rt->amb_int -= 0.05f;
}

void	keyevent(t_rt *rt, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN)
		{
			check_keyevents(rt, e);
			if (e->key.keysym.sym == SDLK_ESCAPE)
				rt->rend.run = FALSE;
			if (e->key.keysym.sym == SDLK_p)
				create_bmp("RT screencap.bmp", &rt->rend.win_buffer);
			printf("amb_int\t= %f\namb_p\t= %f\n", rt->amb_int, rt->amb_p);
		}
		else if (e->type == SDL_WINDOWEVENT \
		&& e->window.event == SDL_WINDOWEVENT_CLOSE)
			rt->rend.run = FALSE;
		else if (e->type == SDL_WINDOWEVENT \
		&& e->window.event == SDL_WINDOWEVENT_EXPOSED)
			draw_to_window(rt);
		rt->redraw = TRUE;
	}
}
