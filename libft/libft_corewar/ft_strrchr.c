/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:04:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/11/24 18:40:54 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	sim;
	char	*r;
	char	*p;
	int		i;

	sim = (char)c;
	r = (char *)s;
	p = NULL;
	i = 0;
	while (*r)
	{
		if (*(r) == sim)
		{
			p = r;
			i++;
		}
		r++;
	}
	if (sim == '\0')
		return (r);
	if (i != 0)
		return (p);
	return (NULL);
}
