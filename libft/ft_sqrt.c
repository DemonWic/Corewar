/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:41:20 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 15:40:22 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int res;
	int div;

	res = nb;
	div = nb;
	if (nb <= 0)
		return (0);
	while (1)
	{
		div = (nb / div + div) / 2;
		if (res > div)
			res = div;
		else if (nb == (res * res))
			return (res);
		else
			return (0);
	}
}
