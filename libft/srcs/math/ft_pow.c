/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:59:51 by eniini            #+#    #+#             */
/*   Updated: 2022/05/28 14:21:01 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Exponentially multiplies base integer [i] to the power of [p].
**	x^0 is always 1.
*/
long long	ft_pow(int i, unsigned int p)
{
	if (!p)
		return (1);
	return (i * ft_pow(i, --p));
}
