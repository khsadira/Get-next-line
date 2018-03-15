/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 12:23:24 by khsadira          #+#    #+#             */
/*   Updated: 2018/03/15 15:40:28 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_backslashn_chr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	my_realloc(char **str)
{
	char	*tmp;
	char	*new;

	if (!(*str))
	{
		if (!((*str) = ft_strnew(BUFF_SIZE + 1)))
			return (0);
		return (1);
	}
	if (!(tmp = ft_strnew(ft_strlen(*str))))
		return (0);
	new = *str;
	ft_strcpy(tmp, *str);
	free(*str);
	if (!(*str = ft_strnew(ft_strlen(tmp) + BUFF_SIZE)))
		return (0);
	ft_strcpy(*str, tmp);
	free(tmp);
	return (1);
}

static int	ft_check_error(char **over, int fd, char **line)
{
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*over))
	{
		if (!(*over = ft_strnew(BUFF_SIZE + 1)))
			return (-1);
	}
	return (1);
}

static int	ft_read_line(char **line, char **over, int fd, int rd)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	int		i;

	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			buf[i] = '\0';
			my_realloc((&*line));
			tmp = over[fd];
			over[fd] = ft_strsub(buf, i + 1, BUFF_SIZE - i);
			free(tmp);
			ft_strcat((*line), buf);
			return (1);
		}
		my_realloc((&*line));
		ft_strcat((*line), buf);
	}
	if (rd == -1)
		return (-1);
	(*line) = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*over[15000];
	int			i;
	char		*tmp;

	if (ft_check_error(&over[fd], fd, line) == -1)
		return (-1);
	(*line) = ft_strdup("");
	if (over[fd][0] != '\0')
	{
		my_realloc((&*line));
		if ((i = ft_backslashn_chr(over[fd])) != -1)
		{
			ft_strncat((*line), over[fd], i);
			tmp = over[fd];
			over[fd] = ft_strsub(over[fd], i + 1, BUFF_SIZE - i);
			free(tmp);
			(*line)[i] = '\0';
			return (1);
		}
		ft_strcpy((*line), over[fd]);
	}
	return (ft_read_line(line, over, fd, 0));
}
