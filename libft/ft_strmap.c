/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 20:04:40 by schakor           #+#    #+#             */
/*   Updated: 2017/11/30 13:25:01 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	size_t	i;

	if (s != NULL && f != NULL)
	{
		if (!(ret = (char *)malloc(sizeof(*ret) * (ft_strlen(s) + 1))))
			return (NULL);
		i = 0;
		while (s[i])
		{
			ret[i] = (*f)(s[i]);
			++i;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
