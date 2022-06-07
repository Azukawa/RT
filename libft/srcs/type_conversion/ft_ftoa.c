/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 12:51:34 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:14:26 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Converts the fractional part of the float into its string representation.
*/
static char	*get_fractional(long double ld, unsigned int p, char *ret)
{
	size_t		i;
	char		*s;

	ft_strcat(ret, ".");
	s = ft_strnew(p + 1);
	i = 1;
	while (i <= p)
	{
		s[i - 1] = (size_t)(ft_pow(10, i) * (ld - (size_t)ld)) % 10 + '0';
		i++;
	}
	if (!s)
		return (NULL);
	ft_strcat(ret, s);
	free(s);
	return (ret);
}

/*
**	Copying negative zero-float byte at a time into an integer should
**	result in a nonzero value due to sign bit being active.
**	(Endianess shouldnt affect this!)
*/
static t_bool	test_negative(float f)
{
	unsigned char	*access;
	unsigned long	comp;
	size_t			i;

	if (f < 0)
		return (TRUE);
	if (f == 0.0)
	{
		access = (unsigned char *)&f;
		i = 0;
		comp = 0;
		while (i < sizeof(float))
		{
			comp |= *access;
			comp <<= __CHAR_BIT__;
			access++;
			i++;
		}
		if (comp)
			return (TRUE);
	}
	return (FALSE);
}

/*
**	Checks if a rounding addition is needed, then calculates its value.
**	Rounding follows 'up to nearest, ties to even'-rule as in the
**	glibc implementation.
**	If [ld + 0.5] downcast result isn't 1, that means there is no need
**	for an rounding addition. Same goes for zero-precision calls.
*/
static long double	ftoa_roundup(long double ld, unsigned int prec)
{
	long double	rounding;
	size_t		temp;

	rounding = 0.5;
	if (ld == rounding)
		return (0);
	temp = ld + rounding;
	if (temp % 2 != 0 && prec == 0 && temp != 1)
		return (0);
	while (prec--)
		rounding /= 10;
	return (rounding);
}

/*
**	Allocates memory for the total result (possible negative sign and decimal
**	separator included) and calls rest of the functions in order.
*/
static char	*compile(long double f, unsigned int prec, t_bool negative)
{
	char		*ret;
	char		*s;

	f += ftoa_roundup(f, prec);
	s = ft_uitoa((size_t)f);
	if (!s)
		return (NULL);
	if (negative)
		ret = ft_strnew(ft_strlen(s + 1) + prec + 3);
	else
		ret = ft_strnew(ft_strlen(s) + prec + 2);
	if (!ret)
		return (NULL);
	if (negative)
		ft_strcat(ret, "-");
	ft_strcat(ret, s);
	free(s);
	if (prec)
		return (get_fractional(f, prec, ret));
	else
		return (ret);
}

/*
**	Simple tests for special values other than signed zero.
**	Negative NaN would need another sign bit check, at which point
**	best portable solution would be to write a signbit() function.
*/

/*
**	Returns a string representation of floating point value [f],
**	with the number of decimals equal to [prec].
*/
char	*ft_ftoa(long double f, unsigned int prec)
{
	t_bool		negative;

	if (!(f == f))
		return (ft_strdup("nan"));
	if (f == (1.0 / 0.0))
		return (ft_strdup("inf"));
	if (f == (-1.0 / 0.0))
		return (ft_strdup("-inf"));
	negative = test_negative((float)f);
	if (f < 0)
		f = -f;
	return (compile(f, prec, negative));
}
