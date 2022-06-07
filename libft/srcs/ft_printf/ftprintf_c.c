/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:02:52 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 17:23:42 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_char(t_printf *f)
{
	if (f->info.is_long)
	{
		ft_putwchar(f->data.wc, f->fd);
		f->writecount += ft_wcharlen(f->data.wc);
	}
	else
	{
		ft_putchar_fd(f->data.unsign_i, f->fd);
		f->writecount++;
	}
}

static void	init_c(t_printf *f)
{
	if (f->info.is_long)
		f->data.wc = va_arg(f->args, wint_t);
	else
		f->data.unsign_i = (unsigned int)va_arg(f->args, int);
}

/*
**	Handles padding to either side of printed char.
*/

int	ftprintf_c(t_printf *f)
{
	char	*str;

	init_c(f);
	if (!f->info.left && f->info.width)
	{
		str = ft_strnew(f->info.width);
		if (!str)
			return (-1);
		ft_memset(str, ' ', f->info.width - 1);
		ft_putstr_fd(str, f->fd);
		free(str);
		f->writecount += (f->info.width - 1);
	}
	printf_char(f);
	if (f->info.left && f->info.width)
	{
		str = ft_strnew(f->info.width);
		if (!str)
			return (-1);
		ft_memset(str, ' ', f->info.width - 1);
		ft_putstr_fd(str, f->fd);
		free(str);
		f->writecount += (f->info.width - 1);
	}
	return (1);
}
