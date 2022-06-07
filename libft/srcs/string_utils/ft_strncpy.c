/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:59:21 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:26 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies at most [len] characters the string [src] to [dst] and returns [dst].
**	If [src] is less than [len] characters long, the remainder of [dst]
**	is filled with `\0' characters. Otherwise, dst is not terminated.
**	Source and destination should not overlap, as the behavior is undefined.
*/
char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	while (i < len && i < srclen)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len && i >= srclen)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
