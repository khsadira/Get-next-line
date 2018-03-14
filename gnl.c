#include "get_next_line.h"

int	ft_backslashn_chr(char *str)
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

int	my_realloc(char **str)
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

int	ft_check_error(char **over, int fd, char **line)
{
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*over))
	{
		if (!(*over = ft_strnew(BUFF_SIZE + 1)))
			return (-1);
	}
	if ((fcntl(fd, F_GETFD, 1)))
		return (-1);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*over = NULL;
	int		rd;
	int		i;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	
	if (ft_check_error(&over, fd, line) == -1)
		return (-1);
	(*line) = ft_strdup("");
	if (over[0] != '\0')
	{
		my_realloc((&*line));
		if ((i = ft_backslashn_chr(over)) != -1)
		{
			ft_strncat((*line), over, i);
			tmp = over;
			over = ft_strsub(over, i + 1, BUFF_SIZE - i);
			free(tmp);
			(*line)[i] = '\0';
			return (1);
		}
		ft_strcpy((*line), over);
	}
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		if ((i = ft_backslashn_chr(buf)) != -1)
		{
			buf[i] = '\0';
			my_realloc((&*line));
			tmp = over;
			over = ft_strsub(buf, i + 1, BUFF_SIZE - i);
			free(tmp);
			ft_strcat((*line), buf);
			return (1);
		}
		my_realloc((&*line));
		ft_strcat((*line), buf);
	}
	(*line) = ft_strdup("");
	return (0);
}

int main(int ar, char **av)
{
	int	fd;
	char	*str;
	int	i;
	fd = open(av[1], O_RDONLY);
	str = NULL;
	while ((i = get_next_line(20, &str)) > 0)
	{
		printf("i = %d || %s\n", i, str);	
	}
	printf("i = %d || %s\n", i, str);
}
