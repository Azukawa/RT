/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:49:27 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 18:03:50 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*add_hex_prefix(t_printf *f, char *p, char *str)
{
	if (f->info.is_hex_l || f->info.is_hex_u)
	{
		if (f->info.zeroed && !f->info.i_prec)
		{
			*str = '0';
			if (f->info.is_hex_l)
				*(str + 1) = 'x';
			else
				*(str + 1) = 'X';
		}
		else
		{
			*p = '0';
			if (f->info.is_hex_l)
				*(p + 1) = 'x';
			else
				*(p + 1) = 'X';
		}
		p += 2;
	}
	return (p);
}

/*
**	Writes possible signs in correct positions.
**	If 0-flag is present, signs are always written in front of zero padding.
*/

char	*ftprintf_sgn(t_printf *f, char *p, char *str, t_bool i)
{
	char	c;

	c = 0;
	if (f->info.negative)
		c = '-';
	else if (f->info.space && !f->info.showsign)
		c = ' ';
	else if (f->info.showsign)
		c = '+';
	if (c)
	{
		if ((f->info.zeroed && !i) || (f->info.zeroed && !f->info.i_prec
				&& !f->info.zero_p && i))
			*str = c;
		else
			*p = c;
		p++;
	}
	return (add_hex_prefix(f, p, str));
}
