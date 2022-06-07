/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:07:38 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:24 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Iterates the list [lst] and applies the function [f] to each link.
*/
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*next;

	if (lst != NULL)
	{
		while (lst)
		{
			next = lst->next;
			f(lst);
			lst = next;
		}
	}
}
