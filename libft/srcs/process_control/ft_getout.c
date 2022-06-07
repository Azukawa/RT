/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:37:00 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 21:48:06 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Prints [str] to stderr, then exits the program
**	with the (EXIT_FAILURE) status.
*/
void	ft_getout(const char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
