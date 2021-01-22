#include "corewar.h"

int get_value(int type, t_cursor *cursor, t_init *data)
{
	int arg1;
	
	arg1 = 0;
	if (type == REG_CODE)
	{
		arg1 = (int)data->arena[cor_addr(cursor->position)];
		if (arg1 >= 1 && arg1 <= REG_NUMBER)
			arg1 = cursor->regs[arg1];
		cursor->position += 1;
	}
	else if (type == IND_CODE)
	{
		arg1 = code_to_int2(data, cursor->position, IND_SIZE) % IDX_MOD;
		arg1 = code_to_int2(data, (cursor->pc + arg1), 4);
		cursor->position += IND_SIZE;
	}
	else if (type == DIR_CODE)
	{
		arg1 = code_to_int2(data, cursor->position, g_op_tab[cursor->op_code].dir);
		cursor->position += g_op_tab[cursor->op_code].dir;
	}
	return (arg1);
}


int op_and(t_cursor *cursor, t_init *data)
{
	char *types;
	int arg1;
	int arg2;
	int arg3;
	
	arg1 = 0;
	arg2 = 0;
	arg3 = 0;
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = get_value(types[0], cursor, data);
	arg2 = get_value(types[1], cursor, data);
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if (arg3 >= 1 && arg3 <= REG_NUMBER)
	{
		cursor->regs[arg3] = arg1 & arg2;
		cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
		cursor->position = cor_addr(cursor->position);
		cursor->pc = cursor->position;
	}
	return (0);
}

int op_or(t_cursor *cursor, t_init *data)
{
	char *types;
	int arg1;
	int arg2;
	int arg3;
	
	arg1 = 0;
	arg2 = 0;
	arg3 = 0;
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = get_value(types[0], cursor, data);
	arg2 = get_value(types[1], cursor, data);
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if (arg3 >= 1 && arg3 <= REG_NUMBER)
	{
		cursor->regs[arg3] = arg1 | arg2;
		cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
		cursor->position = cor_addr(cursor->position);
		cursor->pc = cursor->position;
	}
	return (0);
}

int op_xor(t_cursor *cursor, t_init *data)
{
	char *types;
	int arg1;
	int arg2;
	int arg3;
	
	arg1 = 0;
	arg2 = 0;
	arg3 = 0;
	types = get_types_arg(cursor, data->arena);
	cursor->position += 2;
	arg1 = get_value(types[0], cursor, data);
	arg2 = get_value(types[1], cursor, data);
	arg3 = (int)data->arena[cor_addr(cursor->position)];
	cursor->position += 1;
	if (arg3 >= 1 && arg3 <= REG_NUMBER)
	{
		cursor->regs[arg3] = arg1 ^ arg2;
		cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
		cursor->position = cor_addr(cursor->position);
		cursor->pc = cursor->position;
	}
	return (0);
}


