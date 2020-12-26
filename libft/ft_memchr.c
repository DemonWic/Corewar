/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:33:59 by ahintz            #+#    #+#             */
/*   Updated: 2018/11/30 17:50:58 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	sim;
	unsigned char	*src;
	size_t			i;

	sim = (unsigned char)c;
	src = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(src) == sim)
			return (src);
		src++;
		i++;
	}
	return (NULL);
}
