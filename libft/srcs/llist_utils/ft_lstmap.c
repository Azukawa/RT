/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:19:43 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:27 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Iterate the first link to save new link's head, then loop until lst = NULL
**	save current link to elem, then pass it through the function and malloc
**	a copy of elem's data into the new list, then increment through both lists.
**
**	If function fails to allocate memory for a new element and returns NULL,
**	all previously created lists are freed & deleted.
*/
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*elem;

	if (!lst || !f)
		return (NULL);
	elem = f(lst);
	if (!elem)
		return (NULL);
	head = elem;
	lst = lst->next;
	while (lst)
	{
		elem->next = f(lst);
		if (!elem->next)
			break ;
		elem = elem->next;
		lst = lst->next;
	}
	if (lst)
		ft_lstdel(&head, &ft_elemdel);
	return (head);
}
