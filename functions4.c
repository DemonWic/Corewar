/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:54:54 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 14:54:56 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error_read_file(void)
{
	ft_putstr_fd("ERROR: Can't open file with champion:", 2);
	ft_putstr_fd(" No such file or directory\n", 2);
}

void	error_many_champ(void)
{
	ft_putstr_fd("Too many champions\n", 2);
}

void	error_invalid_head(t_init *data, int num)
{
	ft_putstr_fd("Error: File ", 2);
	ft_putstr_fd(data->champs[num]->file, 2);
	ft_putstr_fd(" has an invalid header\n", 2);
}

int		check_errors2(t_init *data, int num)
{
	if (data->error.no_such_file)
	{
		error_read_file();
		return (1);
	}
	if (data->error.too_many_files)
	{
		error_many_champ();
		return (1);
	}
	return (0);
}

int		cor_addr(int num)
{
	int		res;

	res = num % MEM_SIZE;
	if (res < 0)
		res += MEM_SIZE;
	return (res);
}
