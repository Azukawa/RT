/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:21:49 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 15:05:07 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Converts an unsigned integer [ui] to its string representation.
*/

char	*ft_uitoa(size_t ui)
{
	size_t	uix;
	int		i;
	char	*s;

	uix = ui;
	i = 1;
	while (uix > 9 && i++)
		uix /= 10;
	s = ft_strnew(i);
	while (1)
	{
		s[--i] = ui % 10 + '0';
		ui /= 10;
		if (ui == 0)
			break ;
	}
	return (s);
}
