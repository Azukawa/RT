/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:32:06 by esukava           #+#    #+#             */
/*   Updated: 2022/02/23 13:37:43 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "RTv1.h"

#define BUFF_SIZE 4096
#define FD_MAX 4096

char	*concat(char **line, char *buf)
{
	char		*temp;

	temp = NULL;
	if (*line == NULL)
		temp = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(*line, buf);
		ft_strdel(line);
	}
	*line = ft_strdup(temp);
	ft_strdel(&temp);
	return (*line);
}

static int	seeknewline(const char *s)
{
	int			i;

	i = 0;
	if (s)
	{
		while (s[i] != '\n' && s[i] != '\0')
			i++;
		if (s[i] == '\n')
			return (i);
	}
	return (-1);
}

static int	gnlpt2(char **rem, char **line)
{
	int			n;
	char		*temp;

	if (*rem && *rem[0] != '\0')
	{
		n = seeknewline(*rem);
		if (n == -1)
			*line = ft_strdup(*rem);
		else
		{
			*line = ft_strndup(*rem, n);
			if (*rem + n + 1 != NULL)
			{
				temp = ft_strdup(*rem + n + 1);
				ft_strdel(rem);
				*rem = ft_strdup(temp);
				ft_strdel(&temp);
			}
			else
				ft_strdel(rem);
			return (1);
		}
		ft_strdel(rem);
	}
	return (0);
}

static int	gnlpt3(const int *fd, char **line, char **rem)
{
	int		n;
	int		ret;
	char	buf[BUFF_SIZE + 1];

	ret = read(*fd, buf, BUFF_SIZE);
	while (ret)
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		n = seeknewline(buf);
		if (n == -1)
			*line = concat(line, buf);
		else
		{
			*rem = ft_strdup(buf + n + 1);
			buf[n] = '\0';
			*line = concat(line, buf);
			return (1);
		}
		ret = read(*fd, buf, BUFF_SIZE);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*rem[FD_MAX];
	int			n;

	n = 0;
	if (fd < 0 || fd >= FD_MAX || line == NULL)
		return (-1);
	*line = NULL;
	if (gnlpt2(&rem[fd], line) == 1)
		return (1);
	ft_strdel(&rem[fd]);
	n = gnlpt3(&fd, line, &rem[fd]);
	if (n == 1 || n == -1)
		return (n);
	if (*line != NULL)
		return (1);
	return (0);
}
