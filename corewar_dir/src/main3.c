/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:06:58 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 15:06:59 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		print_arena(t_init *data, int type)
{
	if (type == 32)
		print_buf(data->arena);
	else if (type == 64)
		print_buf2(data->arena);
	data->print_win = 1;
	return (0);
}

int		update_vm(t_init *data, t_vdata *vdata)
{
	int res;

	res = 1;
	if (data->cursors == NULL)
		res = 0;
	if (data->flag_vis)
		update_visio(data, vdata);
	return (res);
}

void	execute(t_init *data)
{
	int		run;
	t_vdata	*vdata;

	run = 1;
	if (data->flag_vis)
		vdata = begin_visio(data);
	while (run)
	{
		if (data->flag_vis)
			run_visio(vdata);
		if (data->flag_dump && data->dump_num == data->cycle && run)
			run = print_arena(data, 32);
		if (data->flag_d && data->d_num == data->cycle && run)
			run = print_arena(data, 64);
		cursors_exec(data);
		if (data->cycle_after_check == data->cycles_to_die ||
			data->cycles_to_die <= 0)
			big_check(data);
		if (data->flag_vis || data->cursors == NULL)
			run = update_vm(data, vdata);
	}
	if (data->flag_vis)
		end_visio(vdata, data);
}

void	cor_num_champ(t_init *data)
{
	int i;

	i = 0;
	while (i < data->pl_count)
	{
		if (data->champs[i] != NULL && data->champs[i]->num == 0)
		{
			data->champs[i]->num = min_in_arr(data);
			data->nums[data->champs[i]->num] = 1;
		}
		i++;
	}
}

int		error_help(t_init *data)
{
	print_help();
	data_free(data);
	return (1);
}
