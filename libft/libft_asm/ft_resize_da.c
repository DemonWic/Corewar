/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resize_da.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:47:04 by loram             #+#    #+#             */
/*   Updated: 2020/01/08 20:47:33 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void			ft_copy(int *to, int *from, unsigned size)
{
	unsigned	i;

	i = 0;
	while (i < size)
	{
		to[i] = from[i];
		i++;
	}
}

int					ft_resize_da(t_da *darr, unsigned new_size)
{
	int			*arr;

	if (!(arr = (int *)malloc(sizeof(int) * darr->size)))
		return (0);
	ft_copy(arr, darr->data, darr->id);
	free(darr->data);
	if (!(darr->data = (int *)malloc(sizeof(int) * new_size)))
	{
		free(arr);
		return (0);
	}
	ft_copy(darr->data, arr, darr->id);
	free(arr);
	darr->size = new_size;
	return (1);
}
