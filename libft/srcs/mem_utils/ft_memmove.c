/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 16:10:54 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:21 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies [len] bytes from [src] to [dst] and returns original value of [dst].
**	Overlapping is ok as copying is always done in a non-destructive manner.
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dststr;
	const unsigned char	*srcstr;

	dststr = dst;
	srcstr = src;
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			dststr[len] = srcstr[len];
	}
	return ((void *)dst);
}
