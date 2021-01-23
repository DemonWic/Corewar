/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:14:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 17:21:17 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_corewar/corewar.h"

void	ft_color(t_init *data, int addr, size_t n, int color)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		data->col_arena[cor_addr(addr)] = color;
		i++;
		addr++;
	}
}
