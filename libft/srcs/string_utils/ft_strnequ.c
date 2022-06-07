/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 20:29:42 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 14:29:51 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *a, char const *b, size_t n)
{
	size_t	i;
	size_t	j;

	if (a && b)
	{
		i = 0;
		j = 0;
		while (j < n)
		{
			if (a[i] != '\0' || b[i] != '\0')
			{
				if ((unsigned char)a[i] > (unsigned char)b[i])
					return (0);
				if ((unsigned char)a[i] < (unsigned char)b[i])
					return (0);
				else
					i++;
			}
			j++;
		}
	}
	return (1);
}
