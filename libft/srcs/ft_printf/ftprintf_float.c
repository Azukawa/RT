/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:07:38 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 18:04:55 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*check_flags(t_printf *f, char *s, size_t conv_l)
{
	size_t	i;
	char	*p;

	if (f->info.left)
	{
		i = 0;
		p = s;
	}
	else
	{
		i = 0;
		if (f->info.width > f->info.f_prec)
		{
			if (f->info.width < conv_l)
				i = 0;
			else
				i = f->info.width - conv_l;
			if ((f->info.space || f->info.showsign || f->info.negative) && i)
				i--;
			if (f->info.zero_p && f->info.alt)
				i--;
		}
		p = &s[i];
	}
	return (ftprintf_sgn(f, p, s, FALSE));
}

static size_t	get_size(t_printf *f)
{
	size_t	i;

	i = ft_strlen(f->conversion);
	if (f->info.showsign || f->info.space || f->info.negative)
		i++;
	if (f->info.f_prec > f->info.fract_i && f->info.f_prec
		> f->info.width)
		return (i + (f->info.f_prec - f->info.fract_i));
	else if (f->info.width > i)
		return (f->info.width);
	else
		return (i);
}

static char	*init_f_str(t_printf *f)
{
	char	*str;
	size_t	str_l;

	if (*f->conversion == '-')
	{
		f->info.negative = 1;
		str = ft_strdup(f->conversion + 1);
		if (!str)
			return (NULL);
		free(f->conversion);
		f->conversion = str;
		str = NULL;
	}
	str_l = get_size(f);
	str = ft_strnew(str_l + 1);
	if (!str)
		return (NULL);
	if (f->info.zeroed && !f->info.left)
		ft_memset(str, '0', str_l);
	else
		ft_memset(str, ' ', str_l);
	return (str);
}

/*
**	Prepends zeroes after conversion result if given precision >
**	converted string length. If alternative form is specified, delimiter
**	is added for values without decimal precision.
*/

int	ftprintf_print_f(t_printf *f)
{
	size_t	conv_l;
	char	*str;
	char	*p;

	str = init_f_str(f);
	if (!str)
		return (-1);
	conv_l = ft_strlen(f->conversion);
	p = check_flags(f, str, conv_l);
	ft_memcpy(p, f->conversion, conv_l);
	p += conv_l;
	if (f->info.f_prec > conv_l)
	{
		ft_memset(p, '0', (f->info.f_prec - f->info.fract_i));
		p += (f->info.f_prec - conv_l);
	}
	if (f->info.alt && (!f->info.f_prec || f->info.zero_p))
		*p = '.';
	ft_putstr_fd(str, f->fd);
	f->writecount += ft_strlen(str);
	free(str);
	free(f->conversion);
	return (1);
}
