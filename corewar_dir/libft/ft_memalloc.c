/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:47:14 by ahintz            #+#    #+#             */
/*   Updated: 2018/11/26 15:35:43 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*res;
	char	*con;
	size_t	i;

	res = (char *)malloc(size);
	if (res == NULL)
		return (NULL);
	i = 0;
	con = res;
	while (i < size)
	{
		*res++ = 0;
		i++;
	}
	return (con);
}
