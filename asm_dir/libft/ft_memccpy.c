/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:13:22 by loram             #+#    #+#             */
/*   Updated: 2019/09/11 18:19:42 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n)
{
	char	*res;
	char	*str;
	char	stop;
	int		i;

	res = (char *)dst;
	str = (char *)src;
	stop = (char)c;
	i = 0;
	while ((n - i) > 0)
	{
		res[i] = str[i];
		if (str[i] == stop)
			return (res + i + 1);
		else
			i++;
	}
	return (NULL);
}
