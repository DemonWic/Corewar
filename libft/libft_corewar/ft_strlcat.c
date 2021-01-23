/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:37:10 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/01 09:46:53 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*d;
	char	*s;
	size_t	k;
	size_t	dlen;

	d = dst;
	s = (char *)src;
	k = size;
	while (k-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	k = size - dlen;
	if (k == 0)
		return (dlen + ft_strlen(s));
	while (*s)
	{
		if (k != 1)
		{
			*d++ = *s;
			k--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}
