/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:12:05 by ahintz            #+#    #+#             */
/*   Updated: 2018/11/24 16:38:23 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char sim;
	char *r;

	sim = (char)c;
	r = (char *)s;
	while (*r)
	{
		if (*(r) == sim)
			return (r);
		r++;
	}
	if (sim == '\0')
		return (r);
	return (NULL);
}
