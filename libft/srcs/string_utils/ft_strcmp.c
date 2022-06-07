/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:41:43 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:54 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Lexicographically compares the null-terminated strings [a] and [b].
**
**	Returns an integer greater than, equal to, or less than 0,
**	according as the [a] is greater than, equal to, or less than the [b].
**
**	Comparison is done with unsigned characters,
**	so that `\200' is greater than `\0'.
*/
int	ft_strcmp(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return (((unsigned char)a[i] - (unsigned char)b[i]));
}
