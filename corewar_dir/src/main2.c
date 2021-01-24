/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:05:35 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 15:05:37 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	pres_champ(t_init *data)
{
	int i;

	i = 0;
	ft_putstr("Introducing contestants...\n");
	while (i < data->pl_count)
	{
		ft_putstr("* Player ");
		ft_putnbr(data->champs[i]->num);
		ft_putstr(", weighing ");
		ft_putnbr(data->champs[i]->size);
		ft_putstr(" bytes, \"");
		ft_putstr(data->champs[i]->name);
		ft_putstr("\" (\"");
		ft_putstr(data->champs[i]->comment);
		ft_putstr("\") !\n");
		i++;
	}
}

void	put_winner(t_init *data)
{
	int k;

	k = data->live_player - 1;
	ft_putstr("Contestant ");
	ft_putnbr(data->champs[k]->num);
	ft_putstr(", \"");
	ft_putstr(data->champs[k]->name);
	ft_putstr("\", has won !\n");
}

int		load_arena(t_init *data)
{
	int i;
	int delta;
	int id;

	delta = MEM_SIZE / data->pl_count;
	i = 0;
	while (i < data->pl_count)
	{
		id = i * delta;
		data->champs[i]->visio_last_live = 0;
		ft_color(data, id, (size_t)data->champs[i]->size, i + 1);
		ft_unmemcpy2(data, id, data->champs[i]->code,
		(size_t)data->champs[i]->size);
		if (add_cursor(data, i, id))
		{
			data_free(data);
			return (1);
		}
		else
			data->live_player = data->cursors->num;
		i++;
	}
	data->cycles_to_die = CYCLE_TO_DIE;
	return (0);
}

void	do_op(t_init *data, t_cursor *buffer)
{
	if (buffer->op_code >= 1 && buffer->op_code <= 16)
	{
		if (check_args_types(data, buffer))
		{
			g_op_tab[buffer->op_code].func(buffer, data);
			buffer->cycle_to_op = 0;
		}
		else
			update_cur(data, buffer);
	}
	else
	{
		buffer->pc = cor_addr(buffer->pc + 1);
		buffer->position = buffer->pc;
	}
}

void	cursors_exec(t_init *data)
{
	t_cursor	*buffer;

	data->cycle++;
	data->cycle_after_check++;
	buffer = data->cursors;
	while (buffer)
	{
		if (buffer->cycle_to_op == 0)
		{
			buffer->op_code = (int)data->arena[cor_addr(buffer->position)];
			if (buffer->op_code >= 1 && buffer->op_code <= 16)
				buffer->cycle_to_op = g_op_tab[buffer->op_code].cycles_to_do;
			else
				buffer->cycle_to_op = 0;
		}
		if (buffer->cycle_to_op > 0)
			buffer->cycle_to_op--;
		if (buffer->cycle_to_op == 0)
			do_op(data, buffer);
		buffer = buffer->next;
	}
}
