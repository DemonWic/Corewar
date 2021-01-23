/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:38:34 by loram             #+#    #+#             */
/*   Updated: 2021/01/02 00:38:37 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memnjoin(const void *s1, const void *s2, size_t num1, size_t num2)
{
	void	*res;

	res = NULL;
	if (s1 && s2)
	{
		res = ft_memalloc(num1 + num2);
		if (!res)
			return (NULL);
		res = ft_memcpy(res, s1, num1);
		res = ft_memcpy(res + num1, s2, num2);
	}
	return (res);
}
