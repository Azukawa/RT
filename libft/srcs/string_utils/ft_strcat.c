/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:58:03 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:43 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Appends a copy of the valid string [b] to the end of the valid string [a]
**	then adds a terminating `\0' and returns a pointer to it.
**	[a] must have sufficient space to hold the result.
*/
char	*ft_strcat(char *a, const char *b)
{
	size_t	a_len;
	size_t	i;

	a_len = ft_strlen(a);
	i = 0;
	while (b[i] != '\0')
	{
		a[a_len + i] = b[i];
		i++;
	}
	a[a_len + i] = '\0';
	return (a);
}
