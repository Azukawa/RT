/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_typecheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:33:55 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 17:20:11 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Catches unsupported inputs after the control character.
**	Otherwise directs program flow into correct argument conversion functions.
**	Returns (-1) if any conversion encounters an issue.
*/

int	ftprintf_typecheck(t_printf *f, const char *s)
{
	if (*s == '\0')
		return (-1);
	if (*s == 's')
		return (ftprintf_str(f));
	else if (*s == 'c')
		return (ftprintf_c(f));
	else if (*s == 'd' || *s == 'i')
		return (ftprintf_convert_i(f));
	else if (*s == 'u' || *s == 'o' || *s == 'x' || *s == 'X')
		return (ftprintf_convert_ui(f, s));
	else if (*s == 'f')
		return (ftprintf_convert_f(f));
	else if (*s == 'p')
		return (ftprintf_convert_p(f, s));
	else if (*s == '%')
	{
		ft_putchar_fd('%', f->fd);
		f->writecount++;
	}
	else if (ft_isalpha(*s))
		return (0);
	return (0);
}
