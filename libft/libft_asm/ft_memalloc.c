/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:44:00 by loram             #+#    #+#             */
/*   Updated: 2019/09/16 20:08:59 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	char	*c;

	if (!(c = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	else
		ft_bzero(c, size);
	return ((void *)c);
}
