#include <stdio.h>
#include "corewar.h"




void data_free(t_init *data)
{
    int i;

    i = 0;
    while (i < data->pl_count)
    {
        if (data->champs[i] != NULL)
        {
            if(data->champs[i]->file != NULL)
                free(data->champs[i]->file);
            if (data->champs[i]->code != NULL)
                free(data->champs[i]->code);
            free(data->champs[i]);
        }
        i++;
    }
    free(data->champs);
    free(data);
}



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



int    validation(int argc, char **argv, t_init *data)
{
    int i;
    int j;
    int buf;

    i = 1;
    j = 0;
    while (i < argc)
    {
        if (ft_valname(argv[i]))
        {
            data->champs[j] = (t_champ *)ft_memalloc(sizeof(t_champ));
            if (data->champs[j] == NULL)
                return (1);
            data->champs[j]->file = ft_strdup(argv[i]);
            data->champs[j]->num = 0;
            j++;
        }
        else if (!ft_strcmp(argv[i], "-n"))
        {
            if (ft_isnumber(argv[i + 1]))
            {
                buf = ft_atoi(argv[i + 1]);
                if (buf > data->pl_count || buf <= 0)
                    data->error.help = 1;
                else if (ft_valname(argv[i + 2]))
                {
                    data->champs[j] = (t_champ *)ft_memalloc(sizeof(t_champ));
                    if (data->champs[j] == NULL)
                        return (0);
                    data->champs[j]->file = ft_strdup(argv[i + 2]);
                    data->champs[j]->num = buf;
                    if (data->nums[buf] == 1)
                        data->error.help = 1;
                    data->nums[buf] = 1;
                    j++;
                    i += 2;
                }
                else
                {
                    data->error.help = 1;
                    break;
                }
            }
            else
            {
                data->error.help = 1;
                break ;
            }
        }
        else if (!ft_strcmp(argv[i], "-dump"))
        {
            if (ft_isnumber(argv[i + 1]) && ft_atoi(argv[i + 1]) >= 0) //TODO check for max int and no more
            {
                data->dump_num = ft_atoi(argv[i + 1]);
                i++;
            }
            else
                data->error.help = 1;
        }
        else if (!ft_strcmp(argv[i], "-d"))
        {
            if (ft_isnumber(argv[i + 1]) && ft_atoi(argv[i + 1]) >= 0) //TODO check for max int and no more
            {
                data->d_num = ft_atoi(argv[i + 1]);
                i++;
            }
            else
                data->error.help = 1;
        }
        else if (!ft_strcmp(argv[i], "-v"))
            data->flag_vis = 1;
        else if (!ft_strcmp(argv[i], "-a"))
            data->flag_aff = 1;
        else
            data->error.help = 1;
        i++;
    }
    return (0);
}



int read_champ(t_init *data)
{
    int i;
    int fd;
    int ret;
    unsigned char buf2[4];

    i = 0;
    while (i < data->pl_count)
    {
        fd = open(data->champs[i]->file, O_RDONLY, 0);
        if (fd == -1)
            data->error.no_such_file = 1;
        else
        {
            ret = read(fd, buf2, 4); //MAGIC HEADER
            if (ret != 4)
                data->error.not_valid_file = 1;
            else if (code_to_int(buf2, 4) != COREWAR_EXEC_MAGIC)
                data->error.invalid_head = 1;


            ret = read(fd, data->champs[i]->name, PROG_NAME_LENGTH); // NAME PLAYER
            if (ret != PROG_NAME_LENGTH)
                data->error.not_valid_file = 1;


            ret = read(fd, buf2, 4); // NULL
            if (ret != 4 || code_to_int(buf2, 4) != 0)
                data->error.invalid_head = 1;


            ret = read(fd, buf2, 4);   // CODE SIZE
            if (ret != 4 || code_to_int(buf2, 4) < 0)
                data->error.invalid_head = 1;
            data->champs[i]->size = code_to_int(buf2, 4);
            if (data->champs[i]->size > CHAMP_MAX_SIZE)
                data->error.large_code = 1;

            ret = read(fd, data->champs[i]->comment, COMMENT_LENGTH);  // COMMENT PLAYER
            if (ret != COMMENT_LENGTH)
                data->error.invalid_head = 1;

            ret = read(fd, buf2, 4); // NULL
            if (ret != 4 || code_to_int(buf2, 4) != 0)
                data->error.invalid_head = 1;

            data->champs[i]->code = (unsigned char *)ft_memalloc(data->champs[i]->size);  // CODE PLAYER
            if (data->champs[i]->code == NULL)
                return (1);
            ret = read(fd, data->champs[i]->code, data->champs[i]->size);
            if (ret != data->champs[i]->size)
                data->error.invalid_head = 1;
            ret = read(fd, buf2, 4);
            if (ret != 0)
                data->error.invalid_head = 1;

        }
        if (check_errors(data, i))
        {
            data_free(data);
            return (1);
        }
        i++;
    }
    return (0);
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
//    new->byte_to_next_op = get_byte_to_do(new, data->arena);
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

int arg_size(char type, t_cursor *cursor)
{
//    int arg_tab[4] ={0, T_REG, T_DIR, T_IND};

    if (type & T_REG)
        return (1);
    if (type & T_DIR)
        return (g_op_tab[cursor->op_code].dir);
    if (type & T_IND)
        return (IND_SIZE);
    return (0);
}

int check_args_types2(t_init *data, t_cursor *cursor)
{
    char *arg_types;
    int i;
    int reg;


    i = 0;
    reg = 0;
    int arg_tab[4] ={0, T_REG, T_DIR, T_IND};
    arg_types = get_types_arg(cursor, data->arena);
    if (arg_types == NULL)
        return (0);
    cursor->position += 1 + g_op_tab[cursor->op_code].code_arg;
    if (arg_types[0] != 0)
    {
        while (i < g_op_tab[cursor->op_code].arg_num) {
            if (!(arg_tab[arg_types[i]] & g_op_tab[cursor->op_code].arg_types[i])) // check args types
                return (0);
            if (arg_tab[arg_types[i]] == T_REG) // check register args
            {
                reg = (int) data->arena[cor_addr(cursor->position)];
                if (!(reg >= 1 && reg <= 16))
                    return (0);
            }
            cursor->position += arg_size(arg_tab[arg_types[i]], cursor);
            i++;
        }
    }
    cursor->position = cursor->pc;
    free(arg_types);
    return (1);
}


int check_args_types(t_init *data, t_cursor *cursor)
{
    char *arg_types;
    int i;
    int reg;


    i = 0;
    reg = 0;
    int arg_tab[4] ={0, T_REG, T_DIR, T_IND};
    arg_types = get_types_arg(cursor, data->arena);
    if (arg_types == NULL)
        return (0);
    cursor->position += 1 + g_op_tab[cursor->op_code].code_arg;
    while (i < g_op_tab[cursor->op_code].arg_num)
    {
        if (!(arg_tab[arg_types[i]] & g_op_tab[cursor->op_code].arg_types[i]))
        {
            ft_memdel((void **)&arg_types);
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < g_op_tab[cursor->op_code].arg_num)
    {
        if (arg_tab[arg_types[i]] == T_REG)
        {
            reg = (int) data->arena[cor_addr(cursor->position)];
            if (!(reg >= 1 && reg <= 16))
            {
                ft_memdel((void **)&arg_types);
                return (0);
            }
        }
        cursor->position += arg_size(arg_tab[arg_types[i]], cursor);
        i++;
    }
    cursor->position = cursor->pc;
    ft_memdel((void **)&arg_types);
    return (1);
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
//    step = get_byte_to_do(cursor, data->arena);
    cursor->position = cor_addr((cursor->position + step));
    cursor->pc = cursor->position;
    ft_memdel((void **)&arg_types);
}

int main(int argc, char **argv) {
    int i;
    int j;
    int buf;
    t_init *data;

    i = 1;
    j = 0;
    data = init_data();
    if (data == NULL)
        exit(1);
    pre_valid(argc, argv, data);
    if (data->pl_count > MAX_PLAYERS)
    {
        error_many_champ();
        return (0);
    } else if (data->error.help == 1)
    {
        print_help();
        return (0);
    }
    if (validation(argc, argv, data))
        return (1);
    if (data->error.help == 1)
    {
        print_help();
        return (0);
    }

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

    if (read_champ(data))
    {
        data_free(data);
        return(1);
    }

    // запись кодов игроков на арену, создание кареток
    sort_champs(data);
    int delta;
    int id;
    delta = MEM_SIZE / data->pl_count;
    i = 0;
    id = 0;
    while (i < data->pl_count)
    {
        id = i * delta;
        ft_color(data, id, (size_t)data->champs[i]->size, i + 1);
        ft_unmemcpy2(data, id, data->champs[i]->code, (size_t)data->champs[i]->size);
//        ft_unmemcpy(&(data->arena[id]), data->champs[i]->code, (size_t)data->champs[i]->size);
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






    i = 0;
    int run;
    run = 1;
    t_cursor *buffer;
    while(run)
    {
        data->cycle++;
        data->cycle_after_check++;
        i++;
        buffer = data->cursors;
        int j = 0;
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
                int res;
                if (buffer->op_code >= 1 && buffer->op_code <= 16)
                {
                    if (check_args_types(data, buffer))
                    {
                        res = g_op_tab[buffer->op_code].func(buffer, data);
                        buffer->cycle_to_op = 0;
                    }
                    else
                        {
//                        printf("ОШИБКА цикл= %i\n", data->cycle);
                        update_cur(data, buffer);
                    }
                }
                else
                    {
                    buffer->pc = cor_addr(buffer->pc + 1);
                    buffer->position = buffer->pc;
                }
//                printf("num = %i opcode = %i cycle = %li cursor->pc = %i cycle_to_op = %i\n", buffer->num, buffer->op_code, data->cycle, buffer->pc, buffer->cycle_to_op);
//                buffer->op_code = 0;
//                buffer->cycle_to_op = 0;
            }
//            printf("cycles_to_die = %i live_count = %i  num = %i opcode = %i cycle = %li cursor->pc = %i cycle_to_op = %i\n", data->cycles_to_die, data->live_count, buffer->number, buffer->op_code, data->cycle, buffer->pc, buffer->cycle_to_op);
            buffer = buffer->next;
            j++;
        }
        if (data->cycle_after_check == data->cycles_to_die || data->cycles_to_die <= 0)
            big_check(data);
        if (data->cursors == NULL)
        {
//            data_free(data);
            run = 0;
        }
        if (data->flag_dump && data->dump_num == i && run)
        {
            print_buf(data->arena);
//            data_free(data);
            run = 0;
        }
        if (data->flag_d && data->d_num == i && run)
        {
            print_buf2(data->arena);
//            data_free(data);
            run = 0;
        }


        // delete
//        if (data->cycle == 204)
//            printf("HELOO\n");
    }
    int k;
    k = data->live_player - 1;
    ft_putstr("Contestant ");
    ft_putnbr(data->champs[k]->num);
    ft_putstr(", \"");
    ft_putstr(data->champs[k]->name);
    ft_putstr("\", has won !\n");
    data_free(data);
//    printf("num cycle = %li\n", i);
//    printf("winner = %i\n", data->live_player);

    return 0;
}
