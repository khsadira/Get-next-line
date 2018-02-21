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
	int	len;

	printf("myrealloc\n");
	//len = ft_strlen(str);
	printf("realloc len\n");
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
	printf("realloc if\n");
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
	{
		printf("!ret\n");
		return (NULL);
	}
	printf("realloc after malloc\n");
	ft_strcpy(ret, str);
	printf("realloc strcpy\n");
	free(str);
	printf("realloc end\n");
	return (ret);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char		*ret;

	printf("strjoin start\n");
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(*ret) * (ft_strlen(s1) + ft_strlen(s2)
						+ 1))))
		return (NULL);
	printf("strjoin after if\n");
	ft_strcpy(ret, s1);
	printf("strjoin after strcpy\n");
	ft_strcat(ret, s2);
	printf("strjoin after strcat\n");
	free(s1);
	printf("strjoin end\n");
	return (ret);
}

char	*ft_strfadd(char *s1, char *s2, int i)
{
	int	j;
	int	a;
	char	*ret;

	a = 0;
	printf("\n ||| strfadd ||| \n\n");
	printf("%s\n",s2);
	while (s1[a])
		a++;
	printf("a = %d\n", a);
	s2[i] = '\0';
	printf("%s\n",s2);
	ret = ft_strfjoin(s1, s2);
//	j = 0;
//	while (j < (i + a))
//	{
//		s1[a++] = s2[i++];
//		j++;
//	}
	printf("end while\n");
	ret[a + i] = '\0';
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


	size = 0;
	if (fd == -1)
	{
		printf("fd = -1\n");
		return (-1);
	}
	while ((rd = read(fd, buf, BUFF_SIZE)))
	{
		//printf("starwhile\n");
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			printf("size = %d\n",size);
			printf("%s\n", *line);
			printf("ici : %c\n", (*line)[size - 1]);
	//		(*line)[size] = '\0';	
		//	printf("back slash a i = %d\n",i);
			size -= i;
			*line = my_realloc(*line, size); 
			*line = ft_strfadd(*line, buf, i);
		//	printf("afterline\n");
			if (!over)
			{
		//		printf("malloc over\n");
				if (!((over = (char *)malloc(sizeof(char) * (i + 1)))))
					return (-1);
			}
			else
				free(over);
			over = ft_strsub(buf, i, (BUFF_SIZE + 1) - i);
			printf("endGNL\n");
			printf("line = %s\n\nover = %s\n",*line,over);
			printf("%s\n",buf);
		//	printf("\n%s\n%s\n",buf,over);
			return (1);
		}
		size += BUFF_SIZE;
	//	printf("endwhile\n");
		*line = my_realloc(*line, size); 
		*line = ft_strfjoin(*line, buf);
	}
	//printf("afterwhile\n");
	return (0);
}

int		main(int ac, char **av)
{
	char	*str;
	int		fd;
	int i =0;
	str = NULL;
	fd = open(av[1], O_RDONLY);
	//while (get_next_line(fd, &str) > 0)
	//{
	//	ft_putendl(str);
	//}
	while(i < 2){
	get_next_line(fd, &str);
	printf("\n\nSALUT\n\n");
	ft_putendl(str);i++;}
	return (0);
}
