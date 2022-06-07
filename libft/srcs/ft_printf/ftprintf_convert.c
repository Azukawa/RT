/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_convert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:02:08 by eniini            #+#    #+#             */
/*   Updated: 2021/04/21 18:50:28 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Adds a prefix to hexadecimal, octal and pointer conversions.
**	As the handling of pointers is implementation-defined by the C standard,
**	this follows the glibc implementation (%#x).
*/

static void	add_prefix(t_printf *f, const char *s)
{
	int		b;

	if (*s == 'o')
	{
		b = 8;
		if (f->info.alt)
			f->info.is_octal = 1;
	}
	else
	{
		b = 16;
		if (*s == 'X' && f->info.alt && f->data.unsign_i != 0)
			f->info.is_hex_u = 1;
		else if ((*s == 'x' && f->info.alt && f->data.unsign_i != 0)
			|| *s == 'p')
			f->info.is_hex_l = 1;
	}
	if (*s == 'X')
		f->conversion = ft_uitoa_base(f->data.unsign_i, b, FALSE);
	else
		f->conversion = ft_uitoa_base(f->data.unsign_i, b, TRUE);
}

/*
**	Glibc-styled null pointer output.
*/

int	ftprintf_convert_p(t_printf *f, const char *s)
{
	f->data.unsign_i = (size_t)va_arg(f->args, void *);
	if (f->data.unsign_i == 0)
	{
		f->conversion = ft_strdup("(nil)");
		if (!f->conversion)
			return (-1);
		return (ftprintf_print_str(f));
	}
	else
	{
		add_prefix(f, s);
		return (ftprintf_print_i(f));
	}
}

int	ftprintf_convert_i(t_printf *f)
{
	if (f->info.is_char)
		f->data.signed_i = (char)va_arg(f->args, int);
	else if (f->info.is_short)
		f->data.signed_i = (short)va_arg(f->args, int);
	else if (f->info.is_long)
		f->data.signed_i = (long int)va_arg(f->args, long int);
	else if (f->info.is_llong)
		f->data.signed_i = va_arg(f->args, long long int);
	else
		f->data.signed_i = (int)va_arg(f->args, int);
	f->conversion = ft_itoa(f->data.signed_i);
	if (!f->conversion)
		return (-1);
	return (ftprintf_print_i(f));
}

/*
**	Unsigned integer conversions ignore sign-related
**	format specifiers [' '] & [+].
*/

int	ftprintf_convert_ui(t_printf *f, const char *s)
{
	if (f->info.is_char)
		f->data.unsign_i = (unsigned char)va_arg(f->args, int);
	else if (f->info.is_short)
		f->data.unsign_i = (unsigned short)va_arg(f->args, int);
	else if (f->info.is_long)
		f->data.unsign_i = (unsigned long)va_arg(f->args, unsigned long);
	else if (f->info.is_llong)
		f->data.unsign_i = va_arg(f->args, unsigned long long);
	else
		f->data.unsign_i = (unsigned int)va_arg(f->args, unsigned int);
	if (*s == 'x' || *s == 'X' || *s == 'o')
		add_prefix(f, s);
	else
		f->conversion = ft_uitoa(f->data.unsign_i);
	if (!f->conversion)
		return (-1);
	f->info.showsign = 0;
	f->info.space = 0;
	return (ftprintf_print_i(f));
}

/*
**	Length of floating point's fractional/decimal part is calculated by finding
**	the delimiting '.' and counting the amount of chars after it.
**	Special values are handled as strings.
*/

int	ftprintf_convert_f(t_printf *f)
{
	char	*delim;

	if (f->info.is_double)
		f->conversion = ft_ftoa(va_arg(f->args, long double), f->info.f_prec);
	else
		f->conversion = ft_ftoa(va_arg(f->args, double), f->info.f_prec);
	if (!f->conversion)
		return (-1);
	if (ft_strequ(f->conversion, "inf") || ft_strequ(f->conversion, "-inf")
		|| ft_strequ(f->conversion, "nan"))
	{
		f->data.s = f->conversion;
		return (ftprintf_print_str(f));
	}
	delim = ft_strchr(f->conversion, '.');
	if (delim)
		f->info.fract_i = ft_strlen(delim + 1);
	return (ftprintf_print_f(f));
}
