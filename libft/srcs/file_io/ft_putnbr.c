/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 19:37:42 by eniini            #+#    #+#             */
/*   Updated: 2020/07/23 12:23:26 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n >= -9 && n <= 9)
	{
		if (n < 0)
		{
			ft_putchar('-');
			ft_putchar(n * (-1) + '0');
		}
		else
			ft_putchar(n + '0');
	}
	else
	{
		ft_putnbr(n / 10);
		if (n > 0)
			ft_putchar((n % 10) + '0');
		else
			ft_putchar((n % 10) * (-1) + '0');
	}
}
