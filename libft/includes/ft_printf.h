/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:31:37 by eniini            #+#    #+#             */
/*   Updated: 2022/05/28 14:14:47 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
**	unistd.h for I/O, stdarg.h for varargs.
**	libft provides type definitions and memory allocation tools.
*/

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_data
{
	void				*p;
	char				*s;
	wchar_t				*ws;
	wint_t				wc;
	signed long long	signed_i;
	unsigned long long	unsign_i;
}						t_data;

typedef struct s_info
{
	unsigned int	i_prec;
	unsigned int	f_prec;
	unsigned int	width;
	unsigned int	is_llong;
	unsigned int	is_long;
	unsigned int	is_short;
	unsigned int	is_char;
	unsigned int	alt;
	unsigned int	space;
	unsigned int	left;
	unsigned int	showsign;
	unsigned int	zeroed;
	unsigned int	is_double;
	unsigned int	zero_p;
	unsigned int	negative;
	unsigned int	is_hex_l;
	unsigned int	is_hex_u;
	unsigned int	is_octal;
	size_t			fract_i;
}					t_info;

typedef struct s_printf
{
	t_data	data;
	t_info	info;
	va_list	args;
	char	*conversion;
	int		fd;
	size_t	writecount;
}			t_printf;

int			ft_printf(const char *s, ...);
int			ft_fprintf(const int fd, const char *s, ...);

const char	*ftprintf_read_args(const char *s, t_printf *f);

int			ftprintf_typecheck(t_printf *f, const char *s);

int			ftprintf_convert_p(t_printf *f, const char *s);
int			ftprintf_convert_i(t_printf *f);
int			ftprintf_convert_ui(t_printf *f, const char *s);
int			ftprintf_convert_f(t_printf *f);

char		*ftprintf_sgn(t_printf *f, char *p, char *s, t_bool i);

int			ftprintf_print_i(t_printf *f);
int			ftprintf_print_f(t_printf *f);
int			ftprintf_print_str(t_printf *f);
int			ftprintf_str(t_printf *f);
int			ftprintf_c(t_printf *f);

#endif
