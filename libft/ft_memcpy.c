/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:29:33 by schakor           #+#    #+#             */
/*   Updated: 2017/11/30 18:43:32 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ucptr1;
	unsigned char	*ucptr2;

	ucptr1 = (unsigned char *)dst;
	ucptr2 = (unsigned char *)src;
	while (n--)
		*ucptr1++ = *ucptr2++;
	return (dst);
}
