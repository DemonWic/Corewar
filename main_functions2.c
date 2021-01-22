#include "corewar.h"

int arg_size(char type, t_cursor *cursor)
{
	if (type & T_REG)
		return (1);
	if (type & T_DIR)
		return (g_op_tab[cursor->op_code].dir);
	if (type & T_IND)
		return (IND_SIZE);
	return (0);
}

int check_args_types2(int a[6], char *arg_types, t_init *data, t_cursor *cursor)
{
	while (a[4] < g_op_tab[cursor->op_code].arg_num)
	{
		if (a[arg_types[a[4]]] == T_REG)
		{
			a[5] = (int) data->arena[cor_addr(cursor->position)];
			if (!(a[5] >= 1 && a[5] <= 16))
			{
				ft_memdel((void **)&arg_types);
				return (0);
			}
		}
		cursor->position += arg_size(a[arg_types[a[4]]], cursor);
		a[4]++;
	}
	cursor->position = cursor->pc;
	ft_memdel((void **)&arg_types);
	return (1);
}

int check_args_types(t_init *data, t_cursor *cursor)
{
	char *arg_types;
	int a[6];
	
	a[0] = 0;
	a[1] = T_REG;
	a[2] = T_DIR;
	a[3] = T_IND;
	a[4] = 0;
	a[5] = 0;
	arg_types = get_types_arg(cursor, data->arena);
	if (arg_types == NULL)
		return (0);
	cursor->position += 1 + g_op_tab[cursor->op_code].code_arg;
	while (a[4] < g_op_tab[cursor->op_code].arg_num)
	{
		if (!(a[arg_types[a[4]]] & g_op_tab[cursor->op_code].arg_types[a[4]]))
		{
			ft_memdel((void **)&arg_types);
			return (0);
		}
		a[4]++;
	}
	a[4] = 0;
	return (check_args_types2(a, arg_types, data, cursor));
}

void update_cur(t_init *data, t_cursor *cursor)
{
	int step;
	int i;
	char *arg_types;
	int arg_tab[4] ={0, T_REG, T_DIR, T_IND};
	
	if (cursor->pc != cursor->position)
		cursor->position = cursor->pc;
	i = 0;
	arg_types = get_types_arg(cursor, data->arena);
	step = 1 + g_op_tab[cursor->op_code].code_arg;
	if (g_op_tab[cursor->op_code].code_arg)
	{
		while (i < g_op_tab[cursor->op_code].arg_num)
		{
			step += arg_size(arg_tab[arg_types[i]], cursor);
			i++;
		}
	}
	else
		step += arg_size(arg_tab[g_op_tab[cursor->op_code].arg_types[0]], cursor);
	cursor->position = cor_addr((cursor->position + step));
	cursor->pc = cursor->position;
	ft_memdel((void **)&arg_types);
}
