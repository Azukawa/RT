/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 20:28:49 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 14:25:08 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *a, char const *b)
{
	size_t	i;

	if (a && b)
	{
		i = 0;
		while (a[i] != '\0' || b[i] != '\0')
		{
			if ((unsigned char)a[i] > (unsigned char)b[i])
				return (0);
			if ((unsigned char)a[i] < (unsigned char)b[i])
				return (0);
			else
				i++;
		}
	}
	return (1);
}
