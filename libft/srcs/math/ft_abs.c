/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 20:21:26 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:35 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Returns the absolute value of [x]. Checks for INT_MIN to avoid overflow.
*/
int	ft_abs(int n)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (2147483647);
		return (-n);
	}
	return (n);
}
