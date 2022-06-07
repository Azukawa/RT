/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:07:22 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:35 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	locates the first occurrence of the null-terminated string [needle]
**	in the null-terminated string [haystack],
**	where not more than [len] characters are searched.
**	Characters that appear after a `\0' are not searched.
**
**	If [needle] is an empty string, [haystack] is returned;
**	if [needle] occurs nowhere in [haystack], NULL is returned; Otherwise
**	a pointer to first character of [needle] in [haystack] is returned.
*/
char	*ft_strnstr(const char *stack, const char *ndl, size_t len)
{
	size_t	i;
	size_t	ndlsize;

	i = 0;
	if (ndl[0] == '\0')
		return ((char *)&stack[0]);
	ndlsize = ft_strlen(ndl);
	while (*stack != '\0' && len >= ndlsize)
	{
		i = 0;
		while (*(stack + i) == *(ndl + i))
		{
			if ((*(ndl + i + 1) == '\0') && (*(stack + i)
					== *(ndl + i)))
				return ((char *)stack);
			i++;
		}
		len--;
		stack++;
	}
	return (NULL);
}
