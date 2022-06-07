/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:19:21 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:01 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	allocates sufficient memory for a copy of the string [s1], does the copy,
**	and returns a pointer to it. If malloc fails, NULL is returned.
*/
char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	i = ft_strlen(s1);
	dup = (char *)malloc(sizeof(dup) * (i + 1));
	if (!dup)
		return (NULL);
	dup = ft_strcpy(dup, s1);
	return (dup);
}
