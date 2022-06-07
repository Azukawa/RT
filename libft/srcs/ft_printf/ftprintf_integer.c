/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:07:19 by eniini            #+#    #+#             */
/*   Updated: 2021/04/21 19:07:12 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	[i] is the offset position within the output string where converted value
**	is written. [i] initialization avoids possible unsigned overflow.
*/

static char	*check_flags(t_printf *f, char *s, size_t conv_l, size_t str_l)
{
	size_t	i;

	if (f->info.left)
		i = 0;
	else
	{
		if (str_l < conv_l || str_l < f->info.i_prec)
			i = 0;
		else
			i = str_l - conv_l;
		if (f->info.i_prec > conv_l)
			i = str_l - f->info.i_prec;
		if ((f->info.showsign || f->info.space || f->info.negative) && i)
			i--;
		if ((f->info.is_hex_l || f->info.is_hex_u) && i >= 2)
			i -= 2;
		else if ((f->info.is_hex_l || f->info.is_hex_u) && i >= 1)
			i -= 1;
		if (*f->conversion == '0' && f->info.zero_p && f->info.width)
			i++;
	}
	return (ftprintf_sgn(f, &s[i], s, TRUE));
}

/*
**	Returns the total size of printed string depending on given width,
**	precision, signs and conversion length.
*/

static size_t	get_size(t_printf *f)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(f->conversion);
	j = 0;
	if (f->info.i_prec <= i && f->info.is_octal && *f->conversion != '0')
		f->info.i_prec = i + 1;
	if (f->info.is_hex_l || f->info.is_hex_u)
		j += 2;
	if (f->info.showsign || f->info.space || f->info.negative)
		i++;
	if ((f->info.i_prec > i + j) && (f->info.i_prec > f->info.width)
		&& (f->info.showsign || f->info.space || f->info.negative))
		return (f->info.i_prec + 1);
	else if (f->info.i_prec > i + j && f->info.i_prec > f->info.width)
		return (f->info.i_prec + j);
	else if (f->info.width > i + j)
		return (f->info.width);
	else
		return (i + j);
}

/*
**	Creates valid string of correct width, then writes converted value
**	into specific position while adding signs and precision zeroes in front.
*/

static char	*init_str(t_printf *f)
{
	char	*str;
	size_t	i;

	i = 0;
	if (f->info.is_hex_l || f->info.is_hex_u)
		i = 2;
	if (*f->conversion == '-')
	{
		f->info.negative = 1;
		str = ft_strdup(f->conversion + 1 + i);
		if (!str)
			return (NULL);
		free(f->conversion);
		f->conversion = str;
		str = NULL;
	}
	str = ft_strnew(get_size(f) + 1 + i);
	if (!str)
		return (NULL);
	return (str);
}

/*
**	Precision of 0 means that no character is written for value of (0) except
**	for the alternative (#) octal implementation (prints a single 0).
*/

int	ftprintf_print_i(t_printf *f)
{
	size_t	conv_l;
	char	*str;
	char	*p;

	str = init_str(f);
	if (!str)
		return (-1);
	conv_l = ft_strlen(f->conversion);
	if (!f->info.i_prec && !f->info.zero_p && f->info.zeroed && !f->info.left)
		ft_memset(str, '0', f->info.width);
	else
		ft_memset(str, ' ', f->info.width);
	p = check_flags(f, str, conv_l, get_size(f));
	if (f->info.i_prec > conv_l)
	{
		ft_memset(p, '0', (f->info.i_prec - conv_l));
		p += (f->info.i_prec - conv_l);
	}
	if (!(*f->conversion == '0' && f->info.zero_p && !f->info.is_octal))
		ft_memcpy(p, f->conversion, conv_l);
	ft_putstr_fd(str, f->fd);
	f->writecount += ft_strlen(str);
	free(str);
	free(f->conversion);
	return (1);
}
