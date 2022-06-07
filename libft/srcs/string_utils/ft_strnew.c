/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 20:27:29 by eniini            #+#    #+#             */
/*   Updated: 2021/04/20 14:25:52 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	while (size--)
		ret[size] = '\0';
	return (ret);
}
