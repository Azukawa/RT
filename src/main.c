/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:12:47 by esukava           #+#    #+#             */
/*   Updated: 2022/11/02 13:49:51 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init(t_rt *rt)
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
	rt->surf = SDL_LoadBMP("./textures/texture.bmp");
	if (!rt->surf || SDL_BYTESPERPIXEL(rt->surf->format->format) != 4)
	{
		write(1, "Failed to load texture. ", 25);
		write(1, "Make sure that .bmp is argb aka bitsperpixel = 4\n", 50);
		exit(1);
	}
	rt->rend.run = TRUE;
	rt->amb_col = (t_color){1, 1, 1};
}

static void	cleanup(t_rt *rt)
{
	SDL_DestroyTexture(rt->rend.win_tex);
	SDL_DestroyRenderer(rt->rend.renderer);
	SDL_DestroyWindow(rt->rend.win);
	SDL_FreeSurface(rt->surf);
	free(rt->rend.win_buffer.px);
	free(rt->object);
	SDL_Quit();
}

void	draw_to_window(t_rt *rt)
{
	if (SDL_LockTexture(rt->rend.win_tex, NULL, \
		&rt->rend.win_pixels, &rt->rend.win_pixel_pitch) < 0)
		exit(EXIT_FAILURE);
	ft_memcpy(rt->rend.win_pixels, rt->rend.win_buffer.px, \
	WIN_H * rt->rend.win_pixel_pitch);
	SDL_UnlockTexture(rt->rend.win_tex);
	if (SDL_RenderCopy(rt->rend.renderer, rt->rend.win_tex, NULL, NULL) < 0)
		exit(EXIT_FAILURE);
	SDL_RenderPresent(rt->rend.renderer);
}

char	*name_screenshot(char *str, int i)
{
		char *ret;
		char *end = ".bmp";
		char *nbr = NULL;
		nbr = ft_memalloc(ft_strlen("000"));
		if (i < 10)
			nbr = ft_strjoin("00", ft_itoa(i));
		else if (i < 100)
			nbr = ft_strjoin("0", ft_itoa(i));
		else if (i < 1000)
			nbr = ft_itoa(i);

		ret = ft_strjoin(str, nbr);
		ret = ft_strjoin(ret, end);
		return(ret);

}

void	update_scene(t_rt *rt)
{
		static int i;

		rt->redraw = TRUE;
		if (i < 120)
		{
		//	rt->cam.pos.x = rt->cam.pos.x + 0.5;
			rt->cam.pos = v_rot_xyz(rt->cam.pos, (t_fvector){0, 0, 3, 0});
		//	rt->light[0].pos = v_rot_xyz(rt->light[0].pos, (t_fvector){0, 0, 3, 0});
		//	rt->cam.dir = v_normalize(v_sub(rt->cam.pos, rt->object[0].pos));
		//	rt->cam.rot = v_normalize(v_sub(rt->object[0].pos, rt->cam.pos));
			rt->cam.rot.z = rt->cam.rot.z + 3;

			create_bmp(name_screenshot("screenshots/screenshot_", i), &rt->rend.win_buffer);
			i++;
		}
		else
			exit(0);
}

static void	loop(t_rt	*rt)
{
	SDL_Event	e;
	int			x;
	int			y;

	keyevent(rt, &e);
	if (rt->redraw == TRUE)
	{
		ft_bzero(rt->rend.win_buffer.px, WIN_H * WIN_W * sizeof(uint32_t));
		y = 0;
		while (y < WIN_H)
		{
			x = 0;
			while (x < WIN_W)
				raytracer(rt, x++, y);
			y++;
		}
		rt->redraw = FALSE;
		draw_to_window(rt);
	}
	update_scene(rt);
}

int	main(int argc, char **argv)
{
	t_rt		rt;

	if (argc != 2)
	{
		ft_putendl("Usage: rtv1 <scene>\n");
		ft_putendl("Check scene_example for formatting guidelines\n");
		exit(EXIT_SUCCESS);
	}
	ft_bzero(&rt, sizeof(t_rt));
	rt.rend.win_buffer.w = WIN_W;
	rt.rend.win_buffer.h = WIN_H;
	rt.rend.win_buffer.px = ft_memalloc(sizeof(uint32_t) * WIN_H * WIN_W);
	if (!rt.rend.win_buffer.px)
	{
		write(1, "fail to malloc\n", 16);
		rt.rend.win_buffer.px = NULL;
		cleanup(&rt);
		return (EXIT_FAILURE);
	}
	init(&rt);
	read_file(&rt, argv[1]);
	while (rt.rend.run)
		loop(&rt);
	cleanup(&rt);
	return (EXIT_SUCCESS);
}
