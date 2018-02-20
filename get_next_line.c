/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 15:51:33 by schakor           #+#    #+#             */
/*   Updated: 2018/02/20 17:13:40 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_backslashn_chr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		++i;
	}
	return (-1);
}

char	*my_realloc(char *str, size_t size)
{
	char 	*ret;
	size_t	len;

	len = ft_strlen(str);
	if (len > size || !str)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
		return (NULL);
	ft_strcpy(ret, str);
	free(str);
	return (ret);
}

char	*ft_strfjoin(char *s1, char const *s2)
{
	char		*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(*ret) * (ft_strlen(s1) + ft_strlen(s2)
						+ 1))))
		return (NULL);
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	free(s1);
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	static char		*over = NULL;
	char			buf[BUFF_SIZE + 1];
	char			*str;
	int				rd;
	int				i;
	int				size;

	size = BUFF_SIZE;
	if (fd == -1)
	{
	}
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			size -= i;
			*line = my_realloc(*line, size); 
			*line = mettre dans line en + les i premier car de buf(*line, buf);
			if (over)
				free(over);
			over = ft_strsub(buf, i, (BUFF_SIZE + 1) - i);
		}
		*line = my_realloc(*line, size += BUFF_SIZE); 
		*line = ft_strfjoin(*line, buf);
	}
	return (0);
}

int		main(int ac, char **av)
{
	char	*str;
	int		fd;

	str = NULL;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		ft_putendl(str);
	}
	return (0);
}
