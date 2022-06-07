/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 16:25:12 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:48 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	locates the first occurrence of the null-terminated string [needle]
**	in the null-terminated string [haystack].
**
**	If [needle] is an empty string, [haystack] is returned;
**	if [needle] occurs nowhere in [haystack], NULL is returned; Otherwise
**	a pointer to first character of [needle] in [haystack] is returned.
*/
char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)&haystack[0]);
	while (*haystack != '\0')
	{
		i = 0;
		while (*(haystack + i) == *(needle + i))
		{
			if ((*(needle + i + 1) == '\0') && (*(haystack + i)
					== *(needle + i)))
				return ((char *)haystack);
			i++;
		}
		haystack++;
	}
	return (NULL);
}
