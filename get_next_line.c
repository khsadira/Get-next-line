/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:32:02 by schakor           #+#    #+#             */
/*   Updated: 2018/02/20 15:05:42 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char *ft_switch(char *str, char *line)
{
	int	i;
	int	j;
	
	i = 0;
	while (str[i] == '\n')
		i++;
	while (str[i])
	{
		if (str[i] == '\n')
			(line)[j++] = str[i++];
	}
	line[j] = '\0';
	return (str);
}

static char	ft_end_of_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (str[i]);
		i++;
	}
}

int		get_next_line(const int fd, char **line)
{
	int			rd;
	static char	*buf;
	char		*str;
	int		i;
	int		j;

	if (!(buf = (char *)malloc(sizeof(*buf) * BUFF_SIZE + 1)))
		return (-1);
	if (!(line = (char **)malloc(sizeof(char *) * BUFF_SIZE + 1)))
		return (-1);
	rd = read(fd, str, BUFF_SIZE);
	str[rd] = '\0';
	if (ft_end_of_line(str) == '\n')
	{
		printf("salut\n");
		ft_putendl(ft_switch(str, &**line));
		return (0)
	}
	while ((rd = read(fd, str, BUFF_SIZE)))
	{
		str[rd] = '\0';
		buf = ft_strcat(buf, str);
	}
}

int main(int ac, char **av)
{
	char **line;

	
}
