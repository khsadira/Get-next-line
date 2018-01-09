/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:32:02 by schakor           #+#    #+#             */
/*   Updated: 2018/01/09 17:09:09 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	int			rd;
	char		*buf;
	static int	i;
	int		j;

	if (!(buf = (char *)malloc(sizeof(*buf) * BUFF_SIZE)))
		return (-1);
	i = 0;
	j = i;
	if ((rd = read(fd, buf, BUFF_SIZE)) != -1)
	{
		buf[rd] = '\0';
		if (buf[i] == '\0')
			return (0);
		while (buf[i] != '\n')
			++i;
		while (j < i)
		{
			(*line)[j] = buf[j];
			j++;
		}
		(*line)[j] = buf[j];
		i++;
		return (1);
	}
	return (-1);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	get_next_line(0, &av[1]);
	printf("%s\n", av[1]);
	return (0);
}
