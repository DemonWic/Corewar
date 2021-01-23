#include "corewar.h"

int op_add(t_cursor *cursor, t_init *data)
{
	int arg1;
	int arg2;
	int arg3;
	
	arg1 = 0;
	arg2 = 0;
	arg3 = 0;
	cursor->position += 2;
	arg1 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	arg2 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if ((arg1 >= 1 && arg1 <= REG_NUMBER) && (arg2 >= 1 && arg2 <= REG_NUMBER) && (arg3 >= 1 && arg3 <= REG_NUMBER))
	{
		cursor->regs[arg3] = cursor->regs[arg1] + cursor->regs[arg2];
		cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
		cursor->position = cor_addr(cursor->position);
		cursor->pc = cursor->position;
	}
	return (0);
}


int op_sub(t_cursor *cursor, t_init *data)
{
	int arg1;
	int arg2;
	int arg3;
	
	arg1 = 0;
	arg2 = 0;
	arg3 = 0;
	cursor->position += 2;
	arg1 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	arg2 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if ((arg1 >= 1 && arg1 <= REG_NUMBER) && (arg2 >= 1 && arg2 <= REG_NUMBER) && (arg3 >= 1 && arg3 <= REG_NUMBER))
	{
		cursor->regs[arg3] = cursor->regs[arg1] - cursor->regs[arg2];
		cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
		cursor->position = cor_addr(cursor->position);
		cursor->pc = cursor->position;
	}
	return (0);
}

int op_zjmp(t_cursor *cursor, t_init *data)
{
	int arg1;
	
	cursor->position += 1;
	arg1 = code_to_int2(data, cursor->position, g_op_tab[cursor->op_code].dir) % IDX_MOD;
	if (cursor->carry == 1)
	{
		cursor->pc += arg1;
		cursor->pc = cor_addr(cursor->pc);
		cursor->position = cursor->pc;
	}
	else
	{
		cursor->position += g_op_tab[cursor->op_code].dir;
		cursor->position = cor_addr(cursor->position);
		cursor->pc = cursor->position;
	}
	return (0);
}

int op_ldi(t_cursor *cursor, t_init *data)
{
	char *types;
	int arg1;
	int arg2;
	int arg3;
	
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = get_value(types[0], cursor, data);
	arg2 = get_value(types[1], cursor, data);
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if (arg3 >= 1 && arg3 <= REG_NUMBER)
	{
		cursor->regs[arg3] = code_to_int2(data, (cursor->pc + ((arg1 + arg2) % IDX_MOD)), 4);
	}
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	ft_memdel((void **)&types);
	return (0);
}

int op_sti(t_cursor *cursor, t_init *data)
{
	char *types;
	unsigned char *num;
	int arg[3];
	int addr;
	
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg[0] = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	arg[1] = get_value(types[1], cursor, data);
	arg[2] = get_value(types[2], cursor, data);
	if (arg[0] >= 1 && arg[0] <= REG_NUMBER)
	{
		num = int_to_code(cursor->regs[arg[0]]);
		addr = cor_addr(cursor->pc + ((arg[1] + arg[2]) % IDX_MOD));
		ft_color(data, addr, REG_SIZE, (cursor->regs[1] * -1));
		ft_unmemcpy2(data, addr, num, REG_SIZE);
		ft_memdel((void **)&num);
	}
	cursor->position = cor_addr(cursor->position);
	cursor->pc = cursor->position;
	ft_memdel((void **)&types);
	return (0);
}
