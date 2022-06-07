/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 18:30:20 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:11:27 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Swaps memory between two parameters. [size] is the sizeof(a && b).
**	Temporary memory address is created to store data between copying.
**	If malloc() fails, no copying takes place.
**	Swapping overlapping memory results in undefined behavior.
*/
void	ft_swap(void *a, void *b, size_t size)
{
	char	*temp;

	temp = malloc(size);
	if (temp)
	{
		ft_memcpy(temp, a, size);
		ft_memcpy(a, b, size);
		ft_memcpy(b, temp, size);
		free(temp);
	}
}
