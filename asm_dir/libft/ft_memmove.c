/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:58:06 by loram             #+#    #+#             */
/*   Updated: 2019/09/11 21:35:13 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str;
	unsigned char	*res;
	int				i;

	str = (unsigned char *)src;
	res = (unsigned char *)dst;
	i = 0;
	if (len == 0)
		return (dst);
	if (!dst && !src)
		return (NULL);
	if (src >= dst)
		while (len - i > 0)
		{
			res[i] = str[i];
			i++;
		}
	else
	{
		i = (int)len;
		while (--i >= 0)
			res[i] = str[i];
	}
	return (dst);
}
