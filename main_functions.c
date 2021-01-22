#include "corewar.h"

void sort_champs(t_init *data)
{
	int i;
	int j;
	t_champ *buf;
	
	i = 0;
	while (i < (data->pl_count - 1))
	{
		j = 0;
		while(j < (data->pl_count - i - 1))
		{
			if (data->champs[j]->num > data->champs[j + 1]->num)
			{
				buf = data->champs[j];
				data->champs[j] = data->champs[j + 1];
				data->champs[j + 1] = buf;
			}
			j++;
		}
		i++;
	}
}

int add_cursor(t_init *data, int champ, int arena_id)
{
	t_cursor *new;
	t_cursor *buf;
	
	new = (t_cursor *)ft_memalloc(sizeof(t_cursor));
	if (new == NULL)
		return (1);
	data->cursors_count += 1;
	data->cursor_num += 1;
	new->number = data->cursor_num;
	new->num = data->champs[champ]->num;
	new->carry = 0;
	new->position = arena_id;
	new->pc = arena_id;
	new->regs[1] = - data->champs[champ]->num;
	new->next = NULL;
	if (data->cursors == NULL)
		data->cursors = new;
	else
	{
		buf = data->cursors;
		new->next = buf;
		data->cursors = new;
	}
	return (0);
}

void kill_cursors(t_init *data)
{
	t_cursor *buf;
	t_cursor *del;
	t_cursor *prev;
	
	buf = data->cursors;
	prev = NULL;
	while (buf)
	{
		if ((data->cycle - buf->cycle_num_live) >= data->cycles_to_die || data->cycles_to_die <= 0)
		{
			data->cursors_count -= 1;
			del = buf;
			buf = buf->next;
			if (prev == NULL)
				data->cursors = buf;
			else
				prev->next = buf;
			ft_memdel((void **)&del);
		}
		else
		{
			prev = buf;
			buf = buf->next;
		}
	}
}

void big_check(t_init *data)
{
	data->check_count += 1;
	kill_cursors(data);
	if (data->check_count == MAX_CHECKS || data->live_count >= NBR_LIVE)
	{
		data->check_count = 0;
		data->cycles_to_die -= CYCLE_DELTA;
	}
	data->cycle_after_check = 0;
	data->live_count = 0;
}


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
