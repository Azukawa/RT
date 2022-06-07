/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:56:55 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:13 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Compares byte string [s1] against byte string [s2].
**	Both strings are assumed to be [n] bytes long.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*str1;
	const char	*str2;
	size_t		i;

	str1 = s1;
	str2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (unsigned char)str1[i] == (unsigned char)str2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
