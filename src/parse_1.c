/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:11:07 by esukava           #+#    #+#             */
/*   Updated: 2022/05/20 13:16:51 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_bool	saveline(char *ret, char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 100)
	{
		while (i < 99 && str[i] != '\0' && str[i] != '\n')
		{
			ret[i] = str[i];
			i++;
		}
		ret[i] = '\0';
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	parse_light(t_rt *rt, char *str)
{
	int	i;

	i = 0;
	if (str[i++] != 'l')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &rt->object[9].pos.x))
		return (FALSE);
	if (!str_to_int(&i, str, &rt->object[9].pos.y))
		return (FALSE);
	if (!str_to_int(&i, str, &rt->object[9].pos.z))
		return (FALSE);
	return (TRUE);
}

t_bool	readscene(char *str, t_rt *rt)
{
	int		fd;
	int		ret;
	int		i;
	char	*output;

	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	ret = get_next_line(fd, &output);
	while (ret > 0 && i < 100)
	{
		saveline(rt->scene[i], output);
		i++;
		free(output);
		ret = get_next_line(fd, &output);
	}
	rt->scene_len = i;
	return (1);
}

t_bool	parse(char *str, t_rt *rt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((!readscene(str, rt)) || \
	(!parse_quantity(rt, rt->scene[j++])) || \
	(!parse_light(rt, rt->scene[j++])) || \
	(!parse_c_pos(rt, rt->scene[j++])) || \
	(!parse_c_dir(rt, rt->scene[j++])))
		return (FALSE);
	j++;
	while (i < rt->object_count)
	{
		if ((!parse_type(rt, rt->scene[j++], i, 0)) || \
		(!parse_pos(rt, rt->scene[j++], i)) || \
		(!parse_dir(rt, rt->scene[j++], i)) || \
		(!parse_r(rt, rt->scene[j++], i)) || \
		(!parse_material(rt, rt->scene[j++], i)) || \
		(!parse_angle(rt, rt->scene[j++], i)))
			return (FALSE);
		j++;
		i++;
	}
	return (TRUE);
}

