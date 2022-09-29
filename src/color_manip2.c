/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manip2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:19:21 by alero             #+#    #+#             */
/*   Updated: 2022/09/29 19:23:08 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	col_mult_colors(t_color a, t_color b)
{
	t_color	result;

	result.red = a.red * b.red;
	result.green = a.green * b.green;
	result.blue = a.blue * b.blue;
	return (result);
}

t_color	col_add(t_color base, t_color mix, float p)
{
	t_color	result;

	if (p == 0.0f)
		return (base);
	if (p == 1.0f)
	{
		result.red = ft_clamp_d(base.red + mix.red, 0.0f, 1.0f);
		result.green = ft_clamp_d(base.green + mix.green, 0.0f, 1.0f);
		result.blue = ft_clamp_d(base.blue + mix.blue, 0.0f, 1.0f);
		return (result);
	}
	result.red = ft_clamp_d(base.red + (p * mix.red), 0.0f, 1.0f);
	result.green = ft_clamp_d(base.green + (p * mix.green), 0.0f, 1.0f);
	result.blue = ft_clamp_d(base.blue + (p * mix.blue), 0.0f, 1.0f);
	return (result);
}
