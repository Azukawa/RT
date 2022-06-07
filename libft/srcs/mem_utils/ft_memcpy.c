/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:48:14 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:16 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies [n] bytes from memory area [src] to memory area [dst]. If
**	[dst] and [src] overlap, behavior is undefined so use ft_memmove instead.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dststr;
	unsigned const char	*srcstr;

	dststr = dst;
	srcstr = src;
	i = 0;
	while (i < n)
	{
		dststr[i] = srcstr[i];
		i++;
	}
	return ((void *)dst);
}
