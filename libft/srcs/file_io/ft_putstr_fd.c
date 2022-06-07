/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:09:46 by eniini            #+#    #+#             */
/*   Updated: 2020/07/23 12:24:51 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		write(fd, s, i);
	}
}
