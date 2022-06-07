/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:39:22 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:47 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Locates the first occurrence of [c] (converted to a char) in string [s].
**	The terminating null character is considered to be part of the string;
**	therefore if [c] is `\0', the functions locate the terminating `\0'.
**
**	returns a pointer to the located character,
**	or NULL if the character does not appear in the string.
*/
char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
