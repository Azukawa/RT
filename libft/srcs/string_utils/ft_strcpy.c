/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:26:32 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:57 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copies the string [src] to [dst] (including the terminating `\0' character)
**	and returns [dst].
**	Source and destination should not overlap, as the behavior is undefined.
*/
char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
