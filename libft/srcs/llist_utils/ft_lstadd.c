/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:49:15 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:12 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adds the list element [new] at the beginning of the list.
**	[alst] is the address of a pointer to the first link of a list.
*/
void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}
