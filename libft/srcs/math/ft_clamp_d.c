/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:05:05 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:57:39 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	Clamps the double [value] between [min] & [max].
*/
double	ft_clamp_d(double value, double min, double max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (value);
}
