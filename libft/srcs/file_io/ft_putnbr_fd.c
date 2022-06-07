/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 15:40:37 by eniini            #+#    #+#             */
/*   Updated: 2020/07/23 12:23:43 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= -9 && n <= 9)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putchar_fd(n * (-1) + '0', fd);
		}
		else
			ft_putchar_fd(n + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		if (n > 0)
			ft_putchar_fd((n % 10) + '0', fd);
		else
			ft_putchar_fd((n % 10) * (-1) + '0', fd);
	}
}
