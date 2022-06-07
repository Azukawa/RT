/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:41:20 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:24 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Writes [len] bytes of value [c] (converted to an unsigned char)
**	to the string [b] and returns it.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return ((void *)b);
}
