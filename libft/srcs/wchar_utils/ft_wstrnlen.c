/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrnlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:51:20 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:19:06 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns the sum byte length of [n] characters of the wide string, or
**	until nul-terminator is reached (which will not be counted).
*/
size_t	ft_wstrnlen(const wchar_t *wstr, size_t n)
{
	size_t	strlen;

	strlen = 0;
	while (*wstr != L'\0' && n)
	{
		strlen += ft_wcharlen((wint_t)(*wstr));
		n--;
		wstr++;
	}
	return (strlen);
}
