/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:46:55 by alero             #+#    #+#             */
/*   Updated: 2022/10/13 15:17:26 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* Light count maximum is set to 10 keep it simple */
void	init_light(t_rt *rt, char *line)
{
	char		*ptr;
	t_fvector	pos;

	if (rt->light_count < 10)
	{
		ptr = (line + 2);
		pos = read_3dvec(ptr);
		ptr = ft_strchr(ptr, ' ');
		if (!ptr)
			ft_getout("excplicitly defined light needs color definition");
		rt->light[rt->light_count].r = 0.5;
		rt->light[rt->light_count].pos = pos;
		rt->light[rt->light_count].color = read_color(ptr);
		printf("light_count = %d\n", rt->light_count);
		rt->light_count++;
	}
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
