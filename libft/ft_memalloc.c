/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memallo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:50:43 by schakor           #+#    #+#             */
/*   Updated: 2017/11/30 19:02:56 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t n)
{
	char	*ret;

	if (!(ret = (char *)malloc(sizeof(*ret) * n)))
		return (NULL);
	ft_bzero(ret, n);
	return (ret);
}
