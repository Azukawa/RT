/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:37 by esukava           #+#    #+#             */
/*   Updated: 2022/10/13 19:29:38 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_keyevents(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_d)
		rt->light[0].pos.z += 5;
	if (e->key.keysym.sym == SDLK_w)
		rt->light[0].pos.x -= 5;
	if (e->key.keysym.sym == SDLK_a)
		rt->light[0].pos.z -= 5;
	if (e->key.keysym.sym == SDLK_s)
		rt->light[0].pos.x += 5;
	if (e->key.keysym.sym == SDLK_q)
		rt->light[0].pos.y += 5;
	if (e->key.keysym.sym == SDLK_e)
		rt->light[0].pos.y -= 5;
	if (e->key.keysym.sym == SDLK_g && rt->is_grayscale)
		rt->is_grayscale = FALSE;
	else if (e->key.keysym.sym == SDLK_g && !rt->is_grayscale)
		rt->is_grayscale = TRUE;
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
