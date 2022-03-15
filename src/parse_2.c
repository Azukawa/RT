/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:27:36 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 20:58:06 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_bool	parse_pos(t_rt *rt, char *str, int index)
{
	int	i;

	i = 0;
	if (str[i++] != 'p')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &rt->object[index].pos.x))
		return (FALSE);
	if (!str_to_int(&i, str, &rt->object[index].pos.y))
		return (FALSE);
	if (!str_to_int(&i, str, &rt->object[index].pos.z))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_dir(t_rt *rt, char *str, int index)
{
	int	i;

	i = 0;
	if (str[i++] != 'd')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &rt->object[index].dir.x))
		return (FALSE);
	if (!str_to_int(&i, str, &rt->object[index].dir.y))
		return (FALSE);
	if (!str_to_int(&i, str, &rt->object[index].dir.z))
		return (FALSE);
	rt->object[index].dir = v_normalize(rt->object[index].dir);
	return (TRUE);
}

t_bool	parse_r(t_rt *rt, char *str, int index)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	if (str[i++] != 'r')
		return (FALSE);
	skip_white(&i, str);
	if (ft_isdigit(str[i]))
	{
		val = ft_atoi(&str[i]);
		rt->object[index].r = val;
		if (rt->object[index].type == CONE)
			rt->object[index].r = 0;
		return (TRUE);
	}
	else
		return (FALSE);
}

//material 0-2
t_bool	parse_material(t_rt *rt, char *str, int index)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	if (str[i++] != 'm')
		return (FALSE);
	skip_white(&i, str);
	if (ft_isdigit(str[i]))
	{
		val = ft_atoi(&str[i]);
		if (val >= 0 && val <= 2)
		{
			rt->object[index].material = val;
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	parse_angle(t_rt *rt, char *str, int index)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	if (str[i++] != 'a')
		return (FALSE);
	skip_white(&i, str);
	if (ft_isdigit(str[i]))
	{
		val = ft_clamp_i(ft_atoi(&str[i]), 5, 70);
		rt->object[index].angle = val;
		return (TRUE);
	}
	return (FALSE);
}
