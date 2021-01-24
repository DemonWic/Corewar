/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sum_2_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:49:20 by loram             #+#    #+#             */
/*   Updated: 2020/01/08 20:49:25 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_da				*ft_sum_2_long(t_da *num1, t_da *num2)
{
	t_da		*res;
	unsigned	i;

	i = (num1->size >= num2->size) ? num1->size : num2->size;
	res = ft_create_da(i);
	i = 0;
	while (res->id < (int)res->size)
	{
		if (((int)num1->size > res->id) && ((int)num2->size > res->id))
			ft_add_da(res, num1->data[res->id] + num2->data[res->id]);
		else if ((int)num1->size > res->id)
			ft_add_da(res, num1->data[res->id]);
		else
			ft_add_da(res, num2->data[res->id]);
	}
	return (ft_norm_long_to_base10(res));
}
