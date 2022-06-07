/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 16:21:30 by eniini            #+#    #+#             */
/*   Updated: 2022/05/28 14:23:47 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns a fresh valid string representing the integer [n] given as argument.
**	If the allocation fails, the function returns NULL.
*/

static int	get_len(intmax_t n)
{
	int		len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*get_str(long n, int len)
{
	char	*s;

	s = ft_strnew(len);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	while (1)
	{
		s[--len] = (n % 10) + '0';
		n /= 10;
		if (n == 0)
			break ;
	}
	return (s);
}

char	*ft_itoa(long long n)
{
	char	*s;
	int		len;

	if (n == INTMAX_MIN)
	{
		s = ft_strdup("-9223372036854775808");
		if (!s)
			return (NULL);
		return (s);
	}
	len = get_len(n);
	return (get_str(n, len));
}
