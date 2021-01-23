/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm_long_to_base10.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:44:33 by loram             #+#    #+#             */
/*   Updated: 2020/03/09 22:44:37 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_da				*ft_norm_long_to_base10(t_da *arr)
{
	unsigned	i;

	i = 0;
	while (i < arr->size - 1)
	{
		if (arr->data[i] >= 10)
		{
			arr->data[i + 1] += arr->data[i] / 10;
			arr->data[i] %= 10;
		}
		i++;
	}
	while (arr->data[i] >= 10)
	{
		ft_add_da(arr, (arr->data[i] / 10));
		arr->data[i] %= 10;
		i++;
	}
	return (arr);
}
