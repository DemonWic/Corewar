/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:19:43 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/01 14:25:20 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*r1;
	unsigned char	*r2;

	i = 0;
	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	while (r1[i] || r2[i])
	{
		if (r1[i] != r2[i])
			return (r1[i] - r2[i]);
		i++;
	}
	return (0);
}
