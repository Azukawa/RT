/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:34:05 by eniini            #+#    #+#             */
/*   Updated: 2022/05/28 14:22:19 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns a string representation of integer [i] written in base[x].
**	Bases over 36 are unsupported, as ones larger are represented with
**	a different formula. Same goes for bases smaller than 2 (unary coding).
**
**	(Note: Specific cases like Base64 should use their own itoa variant.)
*/

static int	convert_hex(long long n, int base, t_bool lcase)
{
	char	cval;

	if (lcase)
		cval = 'a';
	else
		cval = 'A';
	if (n % base >= 10)
		return (n % base - 10 + cval);
	else
		return (n % base + '0');
}

static int	get_len(long long n, int base)
{
	int		len;

	len = 1;
	if (n < 0 && len++)
	{
		n = -n;
		len++;
	}
	while (n >= (long)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

static char	*get_str(long long n, int base, t_bool lcase, int len)
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
		s[--len] = convert_hex(n, base, lcase);
		n /= base;
		if (n == 0)
			break ;
	}
	return (s);
}

char	*ft_itoa_base(long long n, int base, t_bool lcase)
{
	char	*s;
	int		len;

	if (base > 36 || base < 2)
		return (NULL);
	if (n == INTMAX_MIN)
	{
		s = ft_strdup("-9223372036854775808");
		if (!s)
			return (NULL);
		return (s);
	}
	len = get_len(n, base);
	return (get_str(n, base, lcase, len));
}
