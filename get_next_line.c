/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:29:42 by khsadira          #+#    #+#             */
/*   Updated: 2018/05/07 15:03:32 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_backslashn_chr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
	{
		str[i] = '\0';
		return (i);
	}
	return (-1);
}

static char	*ft_strfjoin(char *overflow, char *buff)
{
	int		overflow_size;
	int		buff_size;
	char	*tmp;

	overflow_size = 0;
	buff_size = 0;
	if (overflow)
		overflow_size = ft_strlen(overflow);
	if (buff)
		buff_size = ft_strlen(buff);
	if (!(tmp = (char *)malloc(sizeof(*tmp) *
		(overflow_size + buff_size + 1))))
		return (NULL);
	ft_memcpy(tmp, overflow, overflow_size);
	ft_memcpy(tmp + overflow_size, buff, buff_size);
	tmp[overflow_size + buff_size] = '\0';
	free(overflow);
	return (tmp);
}

static int	ft_check_nl(char **overflow, char **buff, char **line)
{
	char	*tmp;
	int		i;

	*overflow = ft_strfjoin(*overflow, *buff);
	if ((i = ft_backslashn_chr(*overflow)) > -1)
	{
		*line = ft_strdup(*overflow);
		tmp = *overflow;
		*overflow = ft_strdup(*overflow + i + 1);
		free(tmp);
		return (1);
	}
	return (0);
}

int			ft_last_gnl(char **overflow, char **buff, char **line)
{
	free(*buff);
	*line = ft_strdup(*overflow);
	ft_strdel(&(*overflow));
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char *overflow[15000];
	char		*buff;
	int			nl;
	int			rd;

	if (!line || BUFF_SIZE <= 0 || fd < 0 || (rd = read(fd, (char *)0, 0)) < 0)
		return (-1);
	buff = ft_strnew(BUFF_SIZE);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		nl = ft_check_nl(&overflow[fd], &buff, line);
		free(buff);
		if (nl == 1)
			return (1);
		buff = ft_strnew(BUFF_SIZE);
	}
	if ((nl = ft_check_nl(&overflow[fd], &buff, line)))
	{
		free(buff);
		return (1);
	}
	else if (ft_strlen(overflow[fd]) > 0)
		return (ft_last_gnl(&overflow[fd], &buff, line));
	free(buff);
	return (0);
}
