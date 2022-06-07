/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:15:39 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:15:34 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	RIP s[--i] = ui % base >= 10 ? ui % base - 10 + cval : ui % base + '0';

static char	*get_string(size_t ui, int base, char cval, int i)
{
	char	*s;

	s = ft_strnew(i);
	if (!s)
		return (NULL);
	while (1)
	{
		if (ui % base >= 10)
			s[--i] = ui % base - 10 + cval;
		else
			s[--i] = ui % base + '0';
		ui /= base;
		if (ui == 0)
			break ;
	}
	return (s);
}

/*
**	Returns a string representation of unsigned integer [ui] in base[x].
**	Bases over 36 and under 2 are not supported as they don't utilize
**	the same format.
*/
char	*ft_uitoa_base(size_t ui, int base, t_bool lcase)
{
	size_t	uix;
	int		i;
	char	cval;

	if (base > 36 || base < 2)
		return (NULL);
	if (lcase)
		cval = 'a';
	else
		cval = 'A';
	uix = ui;
	i = 1;
	while (uix >= (unsigned int)base)
	{
		i++;
		uix /= base;
	}
	return (get_string(ui, base, cval, i));
}
