/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 17:45:37 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:19 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Appends not more than [n] characters from [b] to the end of [a],
**	then adds a terminating `\0' and returns a pointer to [a].
**	[a] must have sufficient space to hold the result.
*/
char	*ft_strncat(char *a, const char *b, size_t n)
{
	size_t	a_len;
	size_t	i;

	a_len = ft_strlen(a);
	i = 0;
	while (b[i] != '\0' && i < n)
	{
		a[a_len + i] = b[i];
		i++;
	}
	a[a_len + i] = '\0';
	return (a);
}
