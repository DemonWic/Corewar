/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:51:16 by loram             #+#    #+#             */
/*   Updated: 2020/02/13 21:51:19 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void			*ft_memalloc_chars(size_t size, char ch)
{
	char	*c;

	if (!(c = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	else
	{
		ft_bzero(c, size);
		ft_bchars(c, size - 1, ch);
	}
	return ((void *)c);
}
