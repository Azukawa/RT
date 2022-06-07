/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:14:32 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:18 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Copy pointer to next link, delete contents of the current link by
**	applying parameter function to struct data & freeing the link structure
**	then move to the next link, loop until *alst == NULL
*/
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	while (*alst)
	{
		next = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = next;
	}
	*alst = NULL;
}
