/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:46:55 by alero             #+#    #+#             */
/*   Updated: 2022/08/17 15:12:58 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_light(t_rt *rt, char *line)
{
	char		*ptr;
	t_fvector	pos;

	ptr = (line + 2);
	pos = read_3dvec(ptr);
	ptr = ft_strchr(ptr, ' ');
	if (!ptr)
		ft_getout("excplicitly defined light needs color definition");
	rt->light.r = 0.5;
	rt->light.pos = pos;
	rt->light.color = read_color(ptr);
}

void	init_mirror(t_object *object, char *line)
{
	char	*ptr;

	object->mirror = 0;
	if (!line || *line == '\0')
		ft_getout("Missing color definition/or mirror");
	ptr = line + 1;
	if (*ptr == 'm')
		object->mirror = 1;
}
