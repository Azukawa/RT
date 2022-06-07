/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 09:58:32 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:18:59 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Gets the byte length of a wide char (e.g. Unicode character value).
*/
int	ft_wcharlen(wint_t wc)
{
	if (wc > 0x10000)
		return (4);
	else if (wc > 0x800)
		return (3);
	else if (wc > 0x80)
		return (2);
	else
		return (1);
}
