/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:34:27 by eniini            #+#    #+#             */
/*   Updated: 2021/09/28 22:20:20 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <stdlib.h>

//	Macro for standardizing open() calls in G_N_L.
# define BUFF_SIZE 32

//	Generalized datatype to use with linked list functions.
typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

#endif
