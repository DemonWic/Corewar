/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lld_lldi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:14:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 17:21:17 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_cursor	*op_fork2(t_init *data, t_cursor *new, t_cursor *buf, int arg1)
{
	new->position = arg1;
	new->pc = arg1;
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

int			op_fork(t_cursor *cursor, t_init *data)
{
	int			arg1;
	int			i;
	t_cursor	*new;
	t_cursor	*buf;

	i = -1;
	buf = NULL;
	cursor->position += 1;
	arg1 = code_to_int2(data, cursor->position,
	g_op_tab[cursor->op_code].dir) % IDX_MOD;
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
	buf = op_fork2(data, new, buf, arg1);
	return (0);
}

int			op_lld2(t_cursor *cursor, t_init *data, int arg1, int arg2)
{
	arg2 = (int)data->arena[cor_addr(cursor->position)];
	if (arg2 >= 1 && arg2 <= REG_NUMBER)
	{
		cursor->regs[arg2] = arg1;
		cursor->carry = (arg1 == 0) ? 1 : 0;
	}
	cursor->position += 1;
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	return (arg2);
}

int			op_lld(t_cursor *cursor, t_init *data)
{
	char	*types;
	int		arg1;
	int		arg2;

	arg1 = 0;
	arg2 = 0;
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	if (types[0] == DIR_CODE)
	{
		arg1 = code_to_int2(data, cursor->position,
		g_op_tab[cursor->op_code].dir);
		cursor->position += g_op_tab[cursor->op_code].dir;
	}
	else if (types[0] == IND_CODE)
	{
		arg1 = code_to_int2(data, cursor->position, IND_SIZE);
		arg1 = code_to_int2(data, (cursor->pc + arg1), 4);
		cursor->position += IND_SIZE;
	}
	arg2 = op_lld2(cursor, data, arg1, arg2);
	ft_memdel((void **)&types);
	return (0);
}

int			op_lldi(t_cursor *cursor, t_init *data)
{
	char	*types;
	int		arg1;
	int		arg2;
	int		arg3;

	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = get_value(types[0], cursor, data);
	arg2 = get_value(types[1], cursor, data);
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if (arg3 >= 1 && arg3 <= REG_NUMBER)
	{
		cursor->regs[arg3] = code_to_int2(data,
		(cursor->pc + (arg1 + arg2)), 4);
	}
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	ft_memdel((void **)&types);
	return (0);
}
