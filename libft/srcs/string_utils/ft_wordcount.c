/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:24:33 by eniini            #+#    #+#             */
/*   Updated: 2021/01/07 15:54:07 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns the n of symbol sequences delimited by char [c] in the string [s].
*/

size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	wordcount;

	i = 0;
	wordcount = 0;
	if (s[i] != c && s[i] != '\0')
		wordcount++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				wordcount++;
		}
		i++;
	}
	return (wordcount);
}
