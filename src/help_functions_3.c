/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:53:14 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 14:10:00 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_strdel(char **as)
{
	if (as == NULL)
		return ;
	free(*as);
	*as = NULL;
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = (char *)malloc(sizeof(char) * n + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0' && n)
	{
		s2[i] = s1[i];
		i++;
		n--;
	}
	s2[i] = '\0';
	return (s2);
}

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = ft_memalloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	s2 = NULL;
	i = 0;
	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	char	*str;

	i = 0;
	i2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!str)
		return (NULL);
	while (s1[i2] != '\0')
		str[i++] = s1[i2++];
	i2 = 0;
	while (s2[i2] != '\0')
		str[i++] = s2[i2++];
	return (str);
}
