/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:09:58 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 13:12:40 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	sim;
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	sim = (char)c;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		if (*(s) == sim)
		{
			*(d++) = *(s++);
			return (d);
		}
		*(d++) = *(s++);
		i++;
	}
	return (NULL);
}
