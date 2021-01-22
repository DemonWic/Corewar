/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:47:04 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/01 16:38:42 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*res;
	char	*con;

	i = 0;
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	con = res;
	while (i <= size + 1)
		res[i++] = '\0';
	return (con);
}
