/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:23:57 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:15:53 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getstring(char const *s, char c, size_t start)
{
	size_t	index;
	char	*string;

	index = 1;
	while (s[start + index] != c && s[start + index] != '\0')
		index++;
	string = ft_strsub(s, start, index);
	if (!string)
		return (NULL);
	return (string);
}

static char	**ft_initsplit(char const *s, char c)
{
	size_t	wordcount;
	char	**ret;

	wordcount = ft_wordcount(s, c);
	ret = (char **)malloc(sizeof(ret) * (wordcount + 1));
	if (!ret)
		return (NULL);
	if (wordcount == 0)
		ret[0] = NULL;
	ret[wordcount] = NULL;
	return (ret);
}

static char	**ft_dosplit(char const *s, char c, char **ret, size_t wordcount)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < wordcount)
	{
		while (s[i] == c)
		{
			if (s[i] != c && s[i] != '\0')
				break ;
			i++;
		}
		ret[j++] = ft_getstring(s, c, i);
		if (!ret[j])
		{
			ft_free_arr(ret);
			return (NULL);
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (ret);
}

/*
**	Returns a nul-terminated array of substrings copied from [s]
**	delimited by char [c].
*/
char	**ft_strsplit(char const *s, char c)
{
	char	**ret;
	size_t	wordcount;

	ret = ft_initsplit(s, c);
	if (!ret)
		return (NULL);
	wordcount = ft_wordcount(s, c);
	return (ft_dosplit(s, c, ret, wordcount));
}
