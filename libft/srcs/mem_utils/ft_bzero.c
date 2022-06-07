/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:22:28 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:58:10 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Writes [n] zeroed bytes to the string [s].
*/
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = s;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			str[i] = '\0';
			i++;
		}
	}
}
