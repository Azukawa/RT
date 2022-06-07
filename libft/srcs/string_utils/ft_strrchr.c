/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:48:28 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:39 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Locates the last occurrence of [c] (converted to a char) in string [s].
**	The terminating null character is considered to be part of the string;
**	therefore if [c] is `\0', the functions locate the terminating `\0'.
**
**	returns a pointer to the located character,
**	or NULL if the character does not appear in the string.
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	i = ft_strlen(s);
	while (i--)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
