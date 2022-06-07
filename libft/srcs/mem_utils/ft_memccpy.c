/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:52:11 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:04 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies bytes from string [src] to string [dst].
**	If the character [c] (converted to an unsigned char) occurs in the [src],
**	copy stops and pointer to the byte after (c) in the string [dst] is
**	returned. Otherwise, [n] bytes are copied and a NULL pointer is returned.
**
**	Overlap of [src] and [dst] strings results in undefined behaviour.
*/
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*dststr;
	const unsigned char	*srcstr;

	dststr = dst;
	srcstr = src;
	i = 0;
	while (i < n)
	{
		dststr[i] = srcstr[i];
		if (srcstr[i] == (unsigned char)c)
			return ((void *)&dststr[++i]);
		i++;
	}
	return (NULL);
}
