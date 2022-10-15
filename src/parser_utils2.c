/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:46:55 by esukava           #+#    #+#             */
/*   Updated: 2022/10/13 20:45:12 by esukava          ###   ########.fr       */
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
		ft_printf("light_count = %d\n", rt->light_count);
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

void	init_tex(t_object *object, char *line)
{
	char	*ptr;

	object->tx_type = NON;
	if (!line || *line == '\0')
		return ;
	ptr = line + 1;
	if (*ptr == 't' && object->type == PLANE)
	{
		object->tx_type = TEX;
		object->color = (t_color){0, 0, 0};
	}
	if (*ptr == 'c' && (object->type == PLANE
			|| object->type == SPHERE) && object->mirror == 0)
		object->tx_type = CHECK;
}

void	set_color(t_color *color, char *ptr)
{
	if (ptr)
		*color = read_color(ptr);
	else
	{
		ft_printf("no ambient light set!\n");
		*color = (t_color){0, 0, 0};
	}
}

void	set_scale(float *scale, char *ptr)
{
	if (ptr)
		*scale = ft_clamp_d(ft_atof(ptr), 1, 200);
	else
	{
		ft_printf("no texture scale set! Set to 25\n");
		*scale = 25;
	}
}
