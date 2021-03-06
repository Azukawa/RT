/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:38:04 by eniini            #+#    #+#             */
/*   Updated: 2022/06/11 17:08:41 by alero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	read_color(char *line)
{
	char	*ptr;
	t_color	c;
	
	if (!line || *line == '\0')
		ft_getout("Missing color definition");
	ptr = line + 1;
	if (*ptr == 'm')
		return((t_color){0, 0, 0});
	if (!(*ptr >= '0' && *ptr <= '9'))
		ft_getout("Invalid color definition");
	c.red = ft_clamp_i(ft_atoi(ptr), 0, 255) / 255.0f;
	ptr = ft_strchr(line, ',');
	if (!ptr)
		ft_getout("Invalid color definition! (missing RGB information)");
	ptr = (ptr + 1);
	if (!(*ptr >= '0' && *ptr <= '9'))
		ft_getout("Invalid color definition! (Incorrect symbol)");
	c.green = ft_clamp_i(ft_atoi(ptr), 0, 255) / 255.0f;
	ptr = ft_strchr(ptr, ',');
	if (!ptr)
		ft_getout("Invalid color definition! (missing RGB information)");
	ptr = (ptr + 1);
	if (!(*ptr >= '0' && *ptr <= '9'))
		ft_getout("Invalid color definition! (Incorrect symbol)");
	c.blue = ft_clamp_i(ft_atoi(ptr), 0, 255) / 255.0f;
	return (c);
}

/*
*	Read (x,y,z) values from a character string [line].
*	Only floating point values with a period decimal separator delimited with
*	commas are allowed.
*/
t_fvector	read_3dvec(char *line)
{
	t_fvector	v;
	char		*ptr;

	ptr = line;
	if (!(*ptr >= '0' && *ptr <= '9') && (*ptr != '-'))
		ft_getout("Invalid vector init! (Incorrect symbol)");
	v.x = ft_atof(ptr);
	ptr = ft_strchr(line, ',');
	if (!ptr)
		ft_getout("Invalid vector init! (Missing vector Y value");
	ptr = (ptr + 1);
	if (!(*ptr >= '0' && *ptr <= '9') && (*ptr != '-'))
		ft_getout("Invalid vector init! (Incorrect symbol)");
	v.y = ft_atof(ptr);
	ptr = ft_strchr(ptr, ',');
	if (!ptr)
		ft_getout("Invalid vector init! (Missing vector Z value");
	ptr = (ptr + 1);
	if (!(*ptr >= '0' && *ptr <= '9') && (*ptr != '-'))
		ft_getout("Invalid vector init! (Incorrect symbol)");
	v.z = ft_atof(ptr);
	v.w = 1.0f;
	return (v);
}

/*
*	Note: as long as we are rendering only a single camera, it doesn't need to
*	be initalized. Multiple initalizations should not break the program, only
*	rewrite previous coordinates.
*/
void	read_cam(t_rt *rt, char *line)
{
	char		*ptr;
	t_fvector	lookfrom;
	t_fvector	lookat;

	ptr = line;
	lookfrom = read_3dvec(ptr);
	ptr = ft_strchr(line, ' ');
	if (!ptr)
		ft_getout("Invalid camera init! (Incorrect delimiter character)");
	lookat = read_3dvec((ptr + 1));
	rt->cam.pos = lookfrom;
	rt->cam.rot = lookat;
	rt->redraw = TRUE;
	ptr = ft_strchr(ptr + 1, ' ');
	if (ptr)
		rt->amb_col = read_color(ptr);
	else
	{
		ft_printf("no ambient light set!\n");
		rt->amb_col = (t_color){0, 0, 0};
	}
	rt->light.pos = rt->cam.pos;
	rt->light.color = (t_color){1, 1, 1};
}

void	read_objcount(t_rt *rt, char *line)
{
	rt->objcount = ft_atoi(line);
	ft_printf("objectcount: %u\n", rt->objcount);
	if (!rt->objcount)
		ft_getout("Invalid object count declaration!");
	rt->object = (t_object *)malloc(sizeof(t_object) * rt->objcount);
	if (!rt->object)
		ft_getout("Failed to allocate memory for objects.");
}
