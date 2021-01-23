/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_addr_ld_st.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:14:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 17:21:17 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_corewar/corewar.h"

void	op_ld2(t_cursor *cursor, int arg1, int arg2, char *types)
{
	if (arg2 >= 1 && arg2 <= REG_NUMBER)
	{
		cursor->regs[arg2] = arg1;
		cursor->carry = (arg1 == 0) ? 1 : 0;
	}
	cursor->position += 1;
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	ft_memdel((void **)&types);
}

int		op_ld(t_cursor *cursor, t_init *data)
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
		arg1 = code_to_int2(data, (cursor->pc + (arg1 % IDX_MOD)), 4);
		cursor->position += IND_SIZE;
	}
	arg2 = (int)data->arena[cor_addr(cursor->position)];
	op_ld2(cursor, arg1, arg2, types);
	return (0);
}

int		op_st2(t_cursor *cursor, t_init *data, int arg1, int arg2)
{
	arg2 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if ((arg1 >= 1 && arg1 <= REG_NUMBER) && (arg2 >= 1 && arg2 <= REG_NUMBER))
	{
		cursor->regs[arg2] = cursor->regs[arg1];
	}
	return (arg2);
}

void	op_st3(t_cursor *cursor, char *types)
{
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	ft_memdel((void **)&types);
}

int		op_st(t_cursor *cursor, t_init *data)
{
	char			*types;
	unsigned char	*num;
	int				arg1;
	int				arg2;

	arg2 = 0;
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if (types[1] == REG_CODE)
		arg2 = op_st2(cursor, data, arg1, arg2);
	else if (types[1] == IND_CODE)
	{
		arg2 = code_to_int2(data, cursor->position, IND_SIZE) % IDX_MOD;
		cursor->position += IND_SIZE;
		num = int_to_code(cursor->regs[arg1]);
		ft_color(data, cor_addr(cursor->pc + arg2),
		REG_SIZE, (cursor->regs[1] * -1));
		ft_unmemcpy2(data, cor_addr(cursor->pc + arg2), num, REG_SIZE);
		ft_memdel((void **)&num);
	}
	op_st3(cursor, types);
	return (0);
}
