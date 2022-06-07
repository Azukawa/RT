/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:00:28 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:57:16 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	Clamps an integer [value] between [min] & [max].
*/
int	ft_clamp_i(int value, int min, int max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}
