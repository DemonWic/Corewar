/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:38:08 by loram             #+#    #+#             */
/*   Updated: 2019/09/11 16:50:36 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*res;
	unsigned char	*str;
	int				i;

	if (n == 0)
		return (dst);
	if (!dst && !src)
		return (NULL);
	res = (unsigned char *)dst;
	str = (unsigned char *)src;
	i = 0;
	while (n - i > 0)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}
