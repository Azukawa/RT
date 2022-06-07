/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:29:24 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 14:19:15 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *a, char const *b)
{
	char	*concat;
	char	*bookmark;

	if (!a && !b)
		return (NULL);
	concat = (char *)malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 1));
	if (!concat)
		return (NULL);
	bookmark = concat;
	while (*a != '\0')
		*(concat++) = *(a++);
	while (*b != '\0')
		*(concat++) = *(b++);
	*(concat) = '\0';
	return (bookmark);
}
