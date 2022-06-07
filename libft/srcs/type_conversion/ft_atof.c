/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:55:31 by eniini            #+#    #+#             */
/*   Updated: 2022/05/28 14:13:15 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	ft_atof_dec(const char *str, int i)
{
	int			exp;
	int			j;
	long double	ret;

	exp = 0;
	ret = 0.0;
	j = i;
	while (str[j] != '\0' && (str[j] >= 48 && str[j] <= 57))
	{
		exp++;
		j++;
	}
	ret = (long double)ft_atoi_sizet(&str[i]);
	if (ret)
	{
		while (exp)
		{
			ret *= 0.1;
			exp--;
		}
	}
	return (ret);
}

/*
*	Strictly only handles floating point values that use period as the
*	decimal separator. This is because clearest way to initialize vectors
*	is by using comma as the delimiter. i.e. [1.0, 2.5, 0.95].
*/
long double	ft_atof(const char *str)
{
	long double	res;
	int			i;
	int			negcoef;

	i = 0;
	res = 0;
	negcoef = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' \
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		negcoef = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < 48 || str[i] > 57)
		return (0);
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
		return ((res + (ft_atof_dec(str, ++i))) * negcoef);
	return (res * negcoef);
}
