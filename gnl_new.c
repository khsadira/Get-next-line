/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:51:33 by schakor           #+#    #+#             */
/*   Updated: 2018/03/13 16:26:46 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_backslashn_chr(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

char	*my_realloc(char *str, int size)
{
	char 	*ret;

	if (!str)
	{
		if ((!(str = (char *)malloc(sizeof(*str) * (size + 1)))))
			return (NULL);
		return (str);
	}
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
		return (NULL);
	ft_strcpy(ret, str);
	free(str);
	return (ret);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char		*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(*ret) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	free(s1);
	return (ret);
}

int		ft_new_line(int fd, char **line, char **over, int size)
{
	int		i;
	int		rd;
	char		buf[BUFF_SIZE + 1];

	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{

		size += BUFF_SIZE;
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			size -= i;
			buf[i] = '\0';
			(*line) = my_realloc((*line), size);
			(*line) = ft_strcat((*line), buf);
			printf("line = %s\n", (*line));
			(*over) = ft_strsub(buf, i + 1, (BUFF_SIZE + 1) - i);
			printf("line = %s\n", (*line));
			return (1);
		}
		(*line) = my_realloc((*line), size); 
		(*line) = ft_strfjoin((*line), buf);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		*over = NULL;
	int				i;
	char				*tmp;

	int		rd;
	int		size = 0;
	char		buf[BUFF_SIZE + 1];

	if (fd == -1)
		return (-1);
	if (over)
	{
		if ((i = ft_backslashn_chr(over)) != -1)
		{
			tmp = *line;
			(*line) = ft_strsub(over, 0, i);
			free(tmp);
			tmp = over;
			over = ft_strsub(over, i + 1, (BUFF_SIZE - i));
			free(tmp);
			if (over[0] == '\0')
				free(over);
			return (1);
		}
		else
			ft_strcpy((*line), over);

	}
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{

		size += BUFF_SIZE;
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			size -= i;
			buf[i] = '\0';
			(over) = ft_strsub(buf, i + 1, (BUFF_SIZE + 1) - i);
			(*line) = my_realloc((*line), size);
			(*line) = ft_strcat((*line), buf);
			return (1);
		}
		(*line) = my_realloc((*line), size); 
		(*line) = ft_strfjoin((*line), buf);
	}
	return (0);
//	printf("(line = %s\n", *line);
//	return (ft_new_line(fd, &*line, &over, 0));
}
/*
int		main(int ac, char **av)
{
	char	*str;
	int		fd;
	int i =5;
	str = NULL;
	fd = open(av[1], O_RDONLY);
	while ((i = get_next_line(fd, &str))> 0)
	{
		//printf("compteut = %d i = %d\n",cmt,i);
		//printf("%d\n", (i = get_next_line(fd, &str)));
		printf("i = %d | gnl = %s\n",i , str);
	}
	return (0);
}*/
