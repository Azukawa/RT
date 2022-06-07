/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 20:26:56 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:22:43 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Allocates [size] bytes of new memory initialized to 0's and returns it.
**	Note: malloc(0) would result in implementation-dependent behavior,
*	and therefore passing 0 as argument will always return NULL.
*/
void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!size)
		return (NULL);
	mem = (void *)malloc(size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
