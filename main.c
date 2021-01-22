#include "corewar.h"


void    pres_champ(t_init *data)
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

void    put_winner(t_init *data)
{
    int k;

    k = data->live_player - 1;
    ft_putstr("Contestant ");
    ft_putnbr(data->champs[k]->num);
    ft_putstr(", \"");
    ft_putstr(data->champs[k]->name);
    ft_putstr("\", has won !\n");
}

int load_arena(t_init *data)
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
        ft_unmemcpy2(data, id, data->champs[i]->code, (size_t)data->champs[i]->size);
        if (add_cursor(data, i, id))
        {
            data_free(data);
            return(1);
        }
        else
            data->live_player = data->cursors->num;
        i++;
    }
    data->cycles_to_die = CYCLE_TO_DIE;
    return (0);
}


void    cursors_exec(t_init *data)
{
    t_cursor *buffer;

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
        buffer = buffer->next;
    }
}

void    execute(t_init *data)
{
    int run;
    t_vdata *vdata;

    run = 1;
    if (data->flag_vis)
    {
        vdata = (t_vdata*)malloc(sizeof(t_vdata));
        begin_visio(data, vdata);
    }
    while(run)
    {
        if (data->flag_dump && data->dump_num == data->cycle && run)
        {
            print_buf(data->arena);
            data->print_win = 1;
            run = 0;
        }
        if (data->flag_d && data->d_num == data->cycle && run)
        {
            print_buf2(data->arena);
            data->print_win = 1;
            run = 0;
        }
        data->cycle++;
        data->cycle_after_check++;
        cursors_exec(data);
        if (data->cycle_after_check == data->cycles_to_die || data->cycles_to_die <= 0)
            big_check(data);
        if (data->cursors == NULL)
            run = 0;
        if (data->flag_vis)
            update_visio(data, vdata);
    }

    if (data->flag_vis)
        end_visio(vdata);
}

void    cor_num_champ(t_init *data)
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

int main(int argc, char **argv)
{
	t_init *data;

    if (argc < 2)
        print_help();
	data = init_data();
	if (data == NULL)
		exit(1);
	pre_valid(argc, argv, data);
	if (data->pl_count > MAX_PLAYERS)
	{
		error_many_champ();
        data_free(data);
		return (0);
	}
	else if (data->error.help == 1)
	{
		print_help();
        data_free(data);
		return (0);
	}
	if (validation(argc, argv, data))
		return (1);
	if (data->error.help == 1)
	{
		print_help();
        data_free(data);
		return (0);
	}
	cor_num_champ(data);

	if (read_champ(data))
	{
		data_free(data);
		return(1);
	}
	sort_champs(data);

	if (load_arena(data))
        return (1);

	if (!data->flag_vis)
	    pres_champ(data);

	execute(data);

    if (!(data->flag_vis || data->print_win))
        put_winner(data);
	data_free(data);
	return (0);
}
