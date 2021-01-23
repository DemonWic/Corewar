/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:55:21 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/11 19:49:13 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long int		i;
	long int		size;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	size = (long int)(len - 1);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst > src)
		while (size >= i)
		{
			d[size] = s[size];
			size--;
		}
	else
		while (i <= size)
		{
			d[i] = s[i];
			i++;
		}
	return (d);
}
