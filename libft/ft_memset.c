/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:42:04 by ahintz            #+#    #+#             */
/*   Updated: 2018/11/22 13:40:10 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	z;
	char			*s;
	size_t			i;

	z = (char)c;
	s = (char *)b;
	i = 0;
	while (i < len)
	{
		s[i] = z;
		i++;
	}
	return (s);
}
