/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:04:24 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:21 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Takes as a parameter link’s pointer address and frees the memory of link’s
**	content using the function [del], then frees the link’s memory.
**	Finally, the pointer to the link that was just freed is set to NULL.
*/
void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (alst)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
}
