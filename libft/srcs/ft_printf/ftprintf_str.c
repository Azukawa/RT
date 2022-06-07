/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:08:25 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 18:03:44 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size(t_printf *f, size_t strl)
{
	if (f->info.i_prec)
	{
		if (f->info.width > f->info.i_prec)
			return (f->info.width);
		if (f->info.width > strl)
			return (f->info.width);
		if (strl < f->info.i_prec)
			return (strl);
		return (f->info.i_prec);
	}
	if (f->info.width > strl)
		return (f->info.width);
	return (strl);
}

/*
**	If width is larger than strl, we know to that incoming str must be shifted
**	to either side of the output.
**	Precisions smaller than [strl] result in data truncation.
*/

void	handle_offset(t_printf *f, size_t strl, char *str)
{
	char	*p;
	size_t	offset;

	if (f->info.i_prec && f->info.i_prec < strl)
		offset = f->info.i_prec;
	else
		offset = strl;
	if (!f->info.i_prec)
	{
		if (f->info.width < strl)
			p = &str[0];
		else
			p = &str[f->info.width - strl];
	}
	else
	{
		if (f->info.width < offset)
			p = &str[0];
		else
			p = &str[f->info.width - offset];
	}
	if (f->info.left)
		ft_memcpy(str, f->conversion, offset);
	else
		ft_memcpy(p, f->conversion, offset);
}

int	ftprintf_print_str(t_printf *f)
{
	size_t	strl;
	size_t	output_size;
	char	*str;

	strl = ft_strlen(f->conversion);
	output_size = get_size(f, strl);
	str = ft_strnew(output_size);
	if (!str)
		return (-1);
	ft_memset(str, ' ', output_size);
	handle_offset(f, strl, str);
	ft_putstr_fd(str, f->fd);
	f->writecount += ft_strlen(str);
	free(str);
	free(f->conversion);
	return (1);
}

/*
**	User can specify both zero precision and a specific (minimum) width,
**	so that is handled here as well.
*/

static int	print_str_extend(t_printf *f)
{
	char	*s;

	if (f->info.zero_p)
	{
		s = ft_strnew(f->info.width + 1);
		if (!s)
			return (-1);
		ft_memset(s, ' ', f->info.width);
		ft_putstr_fd(s, f->fd);
		f->writecount += f->info.width;
		free(s);
		free(f->conversion);
		return (1);
	}
	if (f->data.ws)
	{
		ft_putwstr(f->data.ws, f->fd);
		f->writecount += ft_wstrlen(f->data.ws);
		return (1);
	}
	else
		return (ftprintf_print_str(f));
}

/*
**	NULL pointers are defined to print out "(null)"
**	in par with Berkeley/Sun implementation.
*/

int	ftprintf_str(t_printf *f)
{
	if (f->info.is_long)
		f->data.ws = va_arg(f->args, wchar_t *);
	else
	{
		f->data.s = va_arg(f->args, char *);
		if (f->data.s == NULL && !f->info.is_long)
			f->conversion = ft_strdup("(null)");
		else if (f->data.s)
			f->conversion = ft_strdup(f->data.s);
		if (!(f->conversion))
			return (-1);
	}
	if (f->data.ws == NULL && f->info.is_long)
	{
		f->data.ws = ft_memalloc(sizeof(wchar_t) * 7);
		if (!f->data.ws)
			return (-1);
		ft_memcpy((void *)f->data.ws, (void *)L"(null)", sizeof(wchar_t) * 6);
	}
	return (print_str_extend(f));
}
