/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:38:23 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:13:09 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Converts the string [str] to int representation.
*/
int	ft_atoi(const char *str)
{
	long int	result;
	int			negative;
	size_t		i;

	result = 0;
	negative = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		negative = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result += (int)str[i] - '0';
		i++;
	}
	return (result * negative);
}
