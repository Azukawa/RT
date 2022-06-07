/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 18:14:24 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 14:32:09 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*strsub;
	size_t	i;
	size_t	strlen;

	if (!s)
		return (NULL);
	strsub = (char *)malloc(sizeof(char) * (len) + 1);
	if (!strsub)
		return (NULL);
	i = 0;
	strlen = ft_strlen(s);
	while (i < len && len <= strlen)
	{
		strsub[i] = s[i + start];
		i++;
	}
	strsub[i] = '\0';
	return (strsub);
}
