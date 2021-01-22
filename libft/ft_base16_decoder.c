/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base16_decoder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:14:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 17:21:17 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_base16_decoder(char *s)
{
	int		i;
	int		nb;
	int		k;
	int		size;
	char	*p;

	size = ft_strlen(s);
	i = 0;
	k = 0;
	p = (char *)malloc((size / 2) + 1);
	while ((i + 1) <= size)
	{
		nb = (s[i] - 48) * 16;
		if (s[i + 1] >= 'A' && s[i + 1] <= 'F')
			nb += s[i + 1] - 55;
		else
			nb += s[i + 1] - 48;
		p[k++] = nb;
		i += 2;
	}
	p[k] = '\0';
	return (p);
}
