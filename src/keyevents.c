/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:37 by esukava           #+#    #+#             */
/*   Updated: 2022/03/29 12:42:43 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	keyevent(t_rt *rt, SDL_Event *e)
{
	if (SDL_WaitEvent(e) > 0)
	{
		if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_w)
				rt->object[9].pos.z -= 5;
			if (e->key.keysym.sym == SDLK_a)
				rt->object[9].pos.x -= 5;
			if (e->key.keysym.sym == SDLK_s)
				rt->object[9].pos.z += 5;
			if (e->key.keysym.sym == SDLK_d)
				rt->object[9].pos.x += 5;
			if (e->key.keysym.sym == SDLK_q)
				rt->object[9].pos.y += 5;
			if (e->key.keysym.sym == SDLK_e)
				rt->object[9].pos.y -= 5;
			if (e->key.keysym.sym == SDLK_ESCAPE)
				rt->rend.run = FALSE;
			rt->cam.dir = v_rot_xyz(rt->cam.dir, rt->cam.rot);
		}
		else if (e->type == SDL_WINDOWEVENT \
		&& e->window.event == SDL_WINDOWEVENT_CLOSE)
			rt->rend.run = FALSE;
		else if (e->type == SDL_WINDOWEVENT \
		&& e->window.event == SDL_WINDOWEVENT_EXPOSED)
			draw_to_window(rt);
		rt->run = TRUE;
	}
}
