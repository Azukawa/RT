/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:04:11 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:19:03 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns the byte length of a null-terminated wide string array
**	(not counting the null terminator itself).
*/
size_t	ft_wstrlen(const wchar_t *wstr)
{
	size_t	strlen;

	strlen = 0;
	while (*wstr != L'\0')
	{
		strlen += ft_wcharlen((wint_t)(*wstr));
		wstr++;
	}
	return (strlen);
}
