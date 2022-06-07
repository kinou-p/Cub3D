/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:42:32 by sadjigui          #+#    #+#             */
/*   Updated: 2021/12/21 23:01:15 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_return(char **str)
{
	int		i;
	char	*s1;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	s1 = ft_substr(*str, 0, i + 1);
	if ((*str)[i] == '\n' && (*str)[i + 1] != '\0')
		tmp = ft_strdup(&(*str)[i + 1]);
	else
		tmp = NULL;
	free(*str);
	*str = tmp;
	if (!*str && s1[0] == '\0')
	{
		free(s1);
		return (NULL);
	}
	return (s1);
}

void	find_line(int fd, char **str, char **buf)
{
	int		i;
	char	*tmp;

	i = 1;
	while (i > 0)
	{
		i = read(fd, *buf, BUFFER_SIZE);
		if (i == -1)
		{
			exit (1);
		}
		(*buf)[i] = '\0';
		tmp = ft_strjoin(*str, *buf);
		free(*str);
		*str = tmp;
		if (ft_check (*str, '\n'))
			break ;
	}
	return ;
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, "", 0) == -1)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	find_line(fd, &str, &buf);
	free (buf);
	return (find_return(&str));
}
