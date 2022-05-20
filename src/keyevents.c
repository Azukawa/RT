/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:37 by esukava           #+#    #+#             */
/*   Updated: 2022/05/20 13:13:58 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
static void	move_cam(t_rt *rt, char axis, float amount)
{
	if (axis == 'x')
	{
		rt->altcam.mod_pos.x += amount;
		rt->altcam.mod_dir.x += amount;
	}
	if (axis ==  'y')
	{
		rt->altcam.mod_pos.y += amount;
		rt->altcam.mod_dir.y += amount;
	}
	if (axis == 'z')
	{
		rt->altcam.mod_pos.z += amount;
		rt->altcam.mod_dir.z += amount;
	}
}

//	Move camera position and lookat in tandem.
static void	ctrl_keyevents(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_w)
		move_cam(rt, 'z', -1.0f);
	if (e->key.keysym.sym == SDLK_s)
		move_cam(rt, 'z', +1.0f);
	if (e->key.keysym.sym == SDLK_d)
		move_cam(rt, 'x', +1.0f);
	if (e->key.keysym.sym == SDLK_a)
		move_cam(rt, 'x', -1.0f);
	if (e->key.keysym.sym == SDLK_q)
		move_cam(rt, 'y', +1.0f);
	if (e->key.keysym.sym == SDLK_e)
		move_cam(rt, 'y', -1.0f);
}

//	Rotate camera around the lookat vector.
static void	shift_keyevents(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_w)
		rt->altcam.rot.x += 5.0f;
	if (e->key.keysym.sym == SDLK_s)
		rt->altcam.rot.x -= 5.0f;
	if (e->key.keysym.sym == SDLK_d)
		rt->altcam.rot.y += 5.0f;
	if (e->key.keysym.sym == SDLK_a)
		rt->altcam.rot.y -= 5.0f;
	if (e->key.keysym.sym == SDLK_q)
		rt->altcam.rot.z += 5.0f;
	if (e->key.keysym.sym == SDLK_e)
		rt->altcam.rot.z -= 5.0f;
	rt->altcam.rot_dir = v_3d_p_rot(rt->altcam.mod_pos, rt->altcam.mod_dir, rt->altcam.rot);
}
*/

static void	nomod_keyevents(t_rt *rt, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_d)
		rt->object[9].pos.z += 5;
	if (e->key.keysym.sym == SDLK_w)
		rt->object[9].pos.x -= 5;
	if (e->key.keysym.sym == SDLK_a)
		rt->object[9].pos.z -= 5;
	if (e->key.keysym.sym == SDLK_s)
		rt->object[9].pos.x += 5;
	if (e->key.keysym.sym == SDLK_q)
		rt->object[9].pos.y += 5;
	if (e->key.keysym.sym == SDLK_e)
		rt->object[9].pos.y -= 5;
}

/*
*	Bitwise AND operation checks if the specific keymodifier mask is active.
*
*	Note: checked like this, ctrl overrides shift modifier if both are pressed.
*/
void	keyevent(t_rt *rt, SDL_Event *e)
{
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_KEYDOWN)
		{
			//if ((SDL_GetModState() & KMOD_LCTRL))
			//	ctrl_keyevents(rt, e);
			//if ((SDL_GetModState() & KMOD_LSHIFT))
			//	shift_keyevents(rt, e);
			//else
			nomod_keyevents(rt, e);
			if (e->key.keysym.sym == SDLK_ESCAPE)
				rt->rend.run = FALSE;
			if (e->key.keysym.sym == SDLK_g)
				rt->keys.is_grayscale = (rt->keys.is_grayscale ? FALSE : TRUE);
			//if (e->key.keysym.sym == SDLK_0)
			//	rt->debug = (rt->debug ? FALSE : TRUE);
			if (e->key.keysym.sym == SDLK_p)
				create_bmp("RT screencap.bmp", &rt->rend.win_buffer);
			if (e->key.keysym.sym == SDLK_m && rt->amb_p < 0.8f)
				rt->amb_p += 0.05f;
			if (e->key.keysym.sym == SDLK_n && rt->amb_p > 0.2f)
				rt->amb_p -= 0.05f;
			// THIS NEEDS A BOOL TO BE HIT
			//if (rt->debug)
			//	init_alt_cam(&rt->altcam, rt->altcam.debug_pos, rt->altcam.debug_dir);
			/*
			else
			{
				init_alt_cam(&rt->altcam, rt->altcam.mod_pos, v_add(rt->altcam.mod_dir, v_sub(rt->altcam.mod_dir, rt->altcam.rot_dir)));
				//
				printf("lookfrom:\tx[%+03.2f] y[%+03.2f] z[%+03.2f]\n", \
				rt->altcam.mod_pos.x, rt->altcam.mod_pos.y, rt->altcam.mod_pos.z);
				printf("lookat:\t\tx[%+03.2f] y[%+03.2f] z[%+03.2f]\n", \
				rt->altcam.mod_dir.x, rt->altcam.mod_dir.y, rt->altcam.mod_dir.z);
				printf("rotation:\tx[%+03.2f] y[%+03.2f] z[%+03.2f]\n\n", \
				rt->altcam.rot.x, rt->altcam.rot.y, rt->altcam.rot.z);
			}*/
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
