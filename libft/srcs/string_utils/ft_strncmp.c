/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:41:43 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:12:22 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Lexicographically compares compares not more than n characters in
**	the null-terminated strings [a] and [b].
**	Characters after '\0' are not compared.
**
**	Returns an integer greater than, equal to, or less than 0,
**	according as the [a] is greater than, equal to, or less than the [b].
**
**	Comparison is done with unsigned characters,
**	so that `\200' is greater than `\0'.
*/
int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (n > 1 && (a[i] != '\0' && b[i] != '\0'))
	{
		if (a[i] == b[i])
		{
			i++;
			n--;
		}
		if (a[i] != b[i])
			break ;
	}
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}
