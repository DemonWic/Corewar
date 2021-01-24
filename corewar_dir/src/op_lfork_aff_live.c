/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork_aff_live.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:14:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 17:21:17 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_cursor	*op_lfork2(t_init *data, t_cursor *buf, t_cursor *new)
{
	if (data->cursors == NULL)
	{
		data->cursors_count++;
		data->cursor_num++;
		new->number = data->cursor_num;
		data->cursors = new;
	}
	else
	{
		buf = data->cursors;
		new->next = buf;
		data->cursors_count++;
		data->cursor_num++;
		new->number = data->cursor_num;
		data->cursors = new;
	}
	return (buf);
}

int			op_lfork(t_cursor *cursor, t_init *data)
{
	int			arg1;
	int			i;
	t_cursor	*new;
	t_cursor	*buf;

	i = -1;
	buf = NULL;
	cursor->position += 1;
	arg1 = code_to_int2(data, cursor->position, g_op_tab[cursor->op_code].dir);
	arg1 = cor_addr(cursor->pc + arg1);
	cursor->position += g_op_tab[cursor->op_code].dir;
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	new = (t_cursor *)ft_memalloc(sizeof(t_cursor));
	if (new == NULL)
		return (1);
	new->cycle_num_live = cursor->cycle_num_live;
	new->carry = cursor->carry;
	new->num = cursor->num;
	while (++i <= REG_NUMBER)
		new->regs[i] = cursor->regs[i];
	new->position = arg1;
	new->pc = arg1;
	buf = op_lfork2(data, buf, new);
	return (0);
}

int			op_aff(t_cursor *cursor, t_init *data)
{
	char	*types;
	int		arg1;
	char	sym;

	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	if ((arg1 >= 1 && arg1 <= REG_NUMBER) && data->flag_aff)
	{
		sym = (char)cursor->regs[arg1];
		ft_putstr("Aff: ");
		ft_putchar(sym);
		ft_putchar('\n');
	}
	ft_memdel((void **)&types);
	return (0);
}

int			op_live(t_cursor *cursor, t_init *data)
{
	int		arg1;

	cursor->cycle_num_live = data->cycle;
	cursor->position += 1;
	arg1 = code_to_int2(data, cursor->position, g_op_tab[cursor->op_code].dir);
	data->live_count++;
	cursor->position += g_op_tab[cursor->op_code].dir;
	arg1 = -arg1;
	if (arg1 >= 1 && arg1 <= data->pl_count)
	{
		data->live_player = arg1;
		data->champs[data->live_player - 1]->visio_last_live = data->cycle;
	}
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	return (0);
}
