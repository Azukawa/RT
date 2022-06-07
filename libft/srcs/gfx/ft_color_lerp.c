/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_lerp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:21:50 by eniini            #+#    #+#             */
/*   Updated: 2021/11/22 20:41:26 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gfx.h"

/*
**	Interpolates each of the RGB color channels between the two given colors
**	in 0xAARRGGBB format.
*/
int	ft_color_lerp(int c1, int c2, double p)
{
	int			r;
	int			g;
	int			b;

	if (c1 == c2)
		return (c1);
	p = ft_clamp_d(p, 0.0, 1.0);
	r = ft_i_lerp((c1 >> 16) & 255, (c2 >> 16) & 255, p);
	g = ft_i_lerp((c1 >> 8) & 255, (c2 >> 8) & 255, p);
	b = ft_i_lerp(c1 & 255, c2 & 255, p);
	return (0 << 24 | r << 16 | g << 8 | b);
}
