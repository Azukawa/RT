/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:47 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 20:58:06 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	cleanup(t_rt *rt)
{
	SDL_DestroyTexture(rt->rend.win_tex);
	SDL_DestroyRenderer(rt->rend.renderer);
	SDL_DestroyWindow(rt->rend.win);
	free(rt->rend.win_buffer.px);
	SDL_Quit();
}

void	draw_to_window(t_rt *rt)
{
	if (SDL_LockTexture(rt->rend.win_tex, NULL, \
		&rt->rend.win_pixels, &rt->rend.win_pixel_pitch) < 0)
		exit(1);
	ft_memcpy(rt->rend.win_pixels, rt->rend.win_buffer.px, \
	WIN_H * rt->rend.win_pixel_pitch);
	SDL_UnlockTexture(rt->rend.win_tex);
	if (SDL_RenderCopy(rt->rend.renderer, rt->rend.win_tex, NULL, NULL) < 0)
		exit(1);
	SDL_RenderPresent(rt->rend.renderer);
}

static void	loop(t_rt	*rt)
{
	SDL_Event	e;

	keyevent(rt, &e);
	if (rt->run == TRUE)
	{
		ft_bzero(rt->rend.win_buffer.px, WIN_H * WIN_W * sizeof(uint32_t));
		ales_rayc(rt);
		draw_to_window(rt);
	}
}

int	main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != 2)
		exit(1);
	ft_bzero(&rt, sizeof(t_rt));
	rt.rend.win_buffer.w = WIN_W;
	rt.rend.win_buffer.h = WIN_H;
	rt.rend.win_buffer.px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	if (!rt.rend.win_buffer.px)
	{
		write(1, "fail to malloc\n", 20);
		rt.rend.win_buffer.px = NULL;
		cleanup(&rt);
		return (-1);
	}
	init(&rt);
	if (parse(argv[1], &rt))
		while (rt.rend.run)
			loop(&rt);
	cleanup(&rt);
	return (0);
}
