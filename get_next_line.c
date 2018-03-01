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

char	*my_realloc(char *str, int size)
{
	char 	*ret;

//	printf("myrealloc\n");
	//len = ft_strlen(str);
//	printf("realloc len\n");
	if (!str)
	{
		if ((!(str = (char *)malloc(sizeof(*str) * (size + 1)))))
			return (NULL);
		return (str);
	}
	//if (len > size || !str)
	//{
	//	printf("str = %s\nlen = %d | size = %d\n", str, len, size);
//		return (NULL);
//	}
//	printf("realloc if\n");
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
	{
//		printf("!ret\n");
		return (NULL);
	}
//	printf("realloc after malloc\n");
	ft_strcpy(ret, str);
//	printf("realloc strcpy\n");
	free(str);
//	printf("realloc end\n");
	return (ret);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char		*ret;

//	printf("strjoin start\n");
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(*ret) * (ft_strlen(s1) + ft_strlen(s2)
						+ 1))))
		return (NULL);
//	printf("strjoin after if\n");
	ft_strcpy(ret, s1);
//	printf("strjoin after strcpy\n");
	ft_strcat(ret, s2);
//	printf("strjoin after strcat\n");
	free(s1);
//	printf("strjoin end\n");
	return (ret);
}

char	*ft_strfadd(char *s1, char *s2, int i)
{
	int	a;
	char	*ret;
	char	c;
	a = 0;
//	printf("\n ||| strfadd ||| \n\n");
//	printf("%s\n",s2);
	while (s1[a])
		a++;
//	printf("a = %d\n", a);
	c = s2[i];
	s2[i] = '\0';
//	printf("%s\n",s2);
	ret = ft_strfjoin(s1, s2);
	s2[i] = c;
//	j = 0;
//	while (j < (i + a))
//	{
//		s1[a++] = s2[i++];
//		j++;
//	}
//	printf("end while\n");
	ret[a + i] = '\0';
	return (ret);
}
/*
int		ft_new_line(int fd, char **line, char **over)
{
	int		size;
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
			(*line) = my_realloc((*line), size);
			(*line) = ft_strfadd((*line), buf, i);
			(*over) = ft_strsub(buf, i + 1, (BUFF_SIZE + 1) - i);
			if ((rd = read(fd, buf, BUFF_SIZE)) != 0 || ft_backslashn_chr((*over)) != -1)
			{
				buf[rd] = '\0';
				(*over) = my_realloc((*over), BUFF_SIZE + rd + 1);
				(*over) = ft_strjoin((*over), buf);
			}
			else
				return (0);
			return (1);
		}
		(*line) = my_realloc((*line), size); 
		(*line) = ft_strfjoin((*line), buf);
	}
	return (0);
}*/

int		get_next_line(const int fd, char **line)
{
	static char		*over = NULL;
	char			buf[BUFF_SIZE + 1];
	int				rd;
	int				i;
	int				size;

	size = 0;
	if (fd == -1)
		return (-1);
	if (over)
	{
		if ((i = ft_backslashn_chr(over)) != -1)
		{
			(*line) = ft_strsub(over, 0, i);
			over = ft_strsub(over, i + 1, (BUFF_SIZE - i));
			if (over[0] == '\0')
			{
				free(over);
				return (1);
			}
			return (1);
		}
		else
		{
			(*line) = ft_strcpy((*line), over);

		}
	}
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		size += BUFF_SIZE;
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			size -= i;
			(*line) = my_realloc((*line), size); 
			(*line) = ft_strfadd((*line), buf, i);
			over = ft_strsub(buf, i + 1, (BUFF_SIZE + 1) - i);
			return (1);
		}
		(*line) = my_realloc(*line, size); 
		(*line) = ft_strfjoin(*line, buf);
	}
	return (0);
}

int		main(int ac, char **av)
{
	char	*str;
	int		fd;
	int i =5;
	ac = 10;
	str = NULL;
	fd = open(av[1], O_RDONLY);
	while ((i > 0))
	{
		//printf("compteut = %d i = %d\n",cmt,i);
		//printf("%d\n", (i = get_next_line(fd, &str)));
		i = get_next_line(fd, &str);
		printf("i = %d | gnl = %s\n",i , str);
	}
	return (0);
}
