/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 12:59:25 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:15 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Adds the list element [new] to the end of list.
**	[alst] is a pointer to the first link of the list.
*/
void	ft_lstaddl(t_list **alst, t_list *new)
{
	t_list	**temp;

	if (alst != NULL && new != NULL)
	{
		temp = alst;
		while ((*temp)->next != NULL)
			*temp = (*temp)->next;
		(*temp)->next = new;
	}
}
