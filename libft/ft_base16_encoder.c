/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base16_encoder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:42:33 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 15:42:39 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_base16_encoder(char *s)
{
	int		i;
	int		j;
	int		nb;
	char	*p;

	nb = ft_strlen(s);
	i = -1;
	j = 0;
	p = (char *)malloc((nb / 2) + 1);
	while (s[++i])
	{
		nb = (int)s[i];
		if (nb > 16)
		{
			p[j++] = nb / 16 + 48;
			nb %= 16;
		}
		if (nb < 9)
			p[j++] = nb + 48;
		if (nb > 9 && nb < 16)
			p[j++] = nb + 55;
	}
	p[j] = '\0';
	return (p);
}
