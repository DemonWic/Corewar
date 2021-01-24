/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_dig_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 14:57:41 by loram             #+#    #+#             */
/*   Updated: 2019/12/18 15:57:35 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_da					*ft_mult_dig_long(t_da *num, int dig)
{
	t_da		*res;
	int			i;

	res = ft_create_da(num->size);
	i = 0;
	while (res->id < (int)res->size)
		ft_add_da(res, num->data[res->id] * dig);
	return (ft_norm_long_to_base10(res));
}
