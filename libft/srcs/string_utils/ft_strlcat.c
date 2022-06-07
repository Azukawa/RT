/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:32:10 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:08 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Appends string [src] to the end of [dst]. It will append at most
**	(dstsize - strlen(dst) - 1) characters. It will then NUL-terminate,
**	unless [dstsize] is 0 or if [dst] was longer than [dstsize].
**	If the [src] and [dst] strings overlap, the behavior is undefined.
**
**	Returns the total length of the string it tries to create.
**	(initial length of [dst] plus the length of [src].)
**
**	If the return value is >= dstsize, the output string has been truncated.
**	It is the caller's responsibility to handle this.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;
	size_t	res;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	res = 0;
	if (dstsize <= dstlen)
		res = srclen + dstsize;
	else
		res = dstlen + srclen;
	i = 0;
	while (src[i] != '\0' && dstlen + 1 < dstsize)
	{
		dst[dstlen] = src[i];
		i++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (res);
}
