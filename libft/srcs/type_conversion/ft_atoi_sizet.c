/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_sizet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:54:41 by eniini            #+#    #+#             */
/*   Updated: 2022/02/14 15:05:35 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	Convert given str to size_t value. Simply ignores a negative sign.
*/
size_t	ft_atoi_sizet(const char *str)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result += (int)str[i] - '0';
		i++;
	}
	return (result);
}
