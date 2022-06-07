/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:49:11 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 17:53:59 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	ANSI C-compliant printf implementation mainly in style of glibc.
**	Supports writing to file descriptors via ft_fprintf(2).
**	Has additional locale-agnostic support for wide characters (UTF-8).
*/

#include "ft_printf.h"

static void	printf_reset(t_printf *f)
{
	f->data.s = NULL;
	f->data.ws = NULL;
	f->conversion = NULL;
	f->info = (t_info){0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

static t_printf	*printf_init(const int fd)
{
	t_printf	*f;

	f = (t_printf *)malloc(sizeof(t_printf));
	if (!f)
		return (NULL);
	f->writecount = 0;
	f->fd = fd;
	return (f);
}

/*
**	Returns 0 if any subfunctions return an error.
*/

static int	loop(t_printf *f, const char *s)
{
	while (*s && *s != '\0')
	{
		if (*s == '%')
		{
			s++;
			printf_reset(f);
			s = ftprintf_read_args(s, f);
			if (!s)
				return (0);
			if (ftprintf_typecheck(f, s) == -1)
				return (0);
			s++;
		}
		else
			f->writecount += write(f->fd, s++, 1);
	}
	if (s == NULL)
		return (0);
	return (1);
}

/*
**	Writes results to stdout.
*/

int	ft_printf(const char *s, ...)
{
	t_printf	*f;
	int			ret_count;

	f = printf_init(1);
	if (!f)
		return (-1);
	va_start(f->args, s);
	if (!(loop(f, s)))
	{
		free(f);
		return (-1);
	}
	va_end(f->args);
	ret_count = (int)f->writecount;
	free(f);
	return (ret_count);
}

/*
**	Writes results to file descriptor [fd].
*/

int	ft_fprintf(const int fd, const char *s, ...)
{
	t_printf	*f;
	int			ret_count;

	f = printf_init(fd);
	if (!f)
		return (-1);
	va_start(f->args, s);
	if (!(loop(f, s)))
	{
		free(f);
		return (-1);
	}
	va_end(f->args);
	ret_count = (int)f->writecount;
	free(f);
	return (ret_count);
}
