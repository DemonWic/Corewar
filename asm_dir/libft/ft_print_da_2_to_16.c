/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_da_2_to_16.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:59:49 by loram             #+#    #+#             */
/*   Updated: 2020/02/13 18:59:52 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Elements in arr are in REVERSE order, i.e [0][0][0][1](in 2-base) == 8 (in
** 10-base)
** (from > to) && (from - to == 4 * n - 1)
*/

void				ft_print_da_2_to_16(t_da *arr, unsigned from, unsigned to)
{
	int			i;
	int			j;
	int			k;
	int			n;

	i = from;
	ft_putstr("0x");
	while ((i - 3) != (int)to)
	{
		k = 1;
		j = 0;
		n = 3;
		while (n >= 0)
		{
			j += arr->data[i - n] * k;
			k *= 2;
			n--;
		}
		if (j < 10)
			ft_putnbr(j);
		else
			ft_putchar(87 + j);
		i = i - 4;
	}
}
