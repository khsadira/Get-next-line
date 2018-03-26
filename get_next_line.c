/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khsadira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:29:42 by khsadira          #+#    #+#             */
/*   Updated: 2018/03/26 11:52:48 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_backslashn_chr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
	{
		str[i] = '\0';
		return (i);
	}
	return (-1);
}

static char	*ft_backslashzero_chr(char *str, int rd)
{
	int	i;
	int	j;
	char	*tmp;
	
	tmp = ft_strnew(BUFF_SIZE);
	i = 0;
	j = 0;
	while (i < rd)
	{
		while (str[i] == '\0' && i < rd)
			i++;
		tmp[j++] = str[i++];
	}
	free(str);
	return (tmp);
}

static char	*ft_strfjoin(char *overflow, char *buff)
{
	int	overflow_size;
	int	buff_size;;
	char	*tmp;

	overflow_size = 0;
	buff_size = 0;
	if (overflow)
		overflow_size = ft_strlen(overflow);
	if (buff)
		buff_size = ft_strlen(buff);
	tmp = (char *)malloc(sizeof(*tmp) * (overflow_size + buff_size + 1));
	ft_memcpy(tmp, overflow, overflow_size);
	ft_memcpy(tmp + overflow_size, buff, buff_size);
	tmp[overflow_size + buff_size] = '\0';
	free(overflow);
	ft_bzero(buff, BUFF_SIZE + 1);
	return (tmp);
}

static int	ft_check_nl(char **overflow, char **buff, char **line)
{
	char	*tmp;
	int	i;

	*overflow = ft_strfjoin(*overflow, *buff);
	i = ft_backslashn_chr(*overflow);
	if (i > -1)
	{
		*line = ft_strdup(*overflow);
		tmp = *overflow;
		*overflow = ft_strdup(*overflow + i + 1);
		free(tmp);
		return (1);
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char *overflow[15000];
	char		*buff;
	int		i;
	int		rd;

	buff = ft_strnew(BUFF_SIZE);
	if (!line || BUFF_SIZE <= 0 || fd < 0 || (rd = read(fd, buff, 0)) < 0)
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff = ft_backslashzero_chr(buff, rd);
		i = ft_check_nl(&overflow[fd], &buff, line);
		free(buff);
		if (i == 1)
			return (1);
		buff = ft_strnew(BUFF_SIZE);
	}
	if ((i = ft_check_nl(&overflow[fd], &buff, line)))
		return (1);
	else if (ft_strlen(overflow[fd]) > 0)
	{
		*line = ft_strdup(overflow[fd]);
		ft_strdel(&overflow[fd]);
		return (1);
	}
	return (i);
}
