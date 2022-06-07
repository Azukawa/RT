/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:28:18 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:56:30 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Creates a new link which (content) and (content_size) are initialized
**	by copy of the parameters of the function and which (next) is NULL.
**
**	If the [content] is NULL, link's (content) is NULL and its (content_size)
**	is 0 even if [content_size] isn’t.
*/
t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (!content)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = (void *)malloc(content_size);
		if (!new->content)
		{
			free(new);
			return (NULL);
		}
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
