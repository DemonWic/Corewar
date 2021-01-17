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
        else if (!ft_strcmp(argv[i], "-v"))
            data->flag_vis = 1;
        else if (!ft_strcmp(argv[i], "-v"))
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

int check_all(t_init *data, t_cursor *cursor)
{

    return (1);
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
        ft_color(data, &(data->col_arena[id]), (size_t)data->champs[i]->size, i + 1);
        ft_unmemcpy(&(data->arena[id]), data->champs[i]->code, (size_t)data->champs[i]->size);
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
                buffer->op_code = (int)data->arena[buffer->position];
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
                if (buffer->op_code >= 1 && buffer->op_code <= 16 && check_all(data, buffer))
                    res = g_op_tab[buffer->op_code].func(buffer, data);
                else
                    {
                    buffer->pc = cor_addr(buffer->pc + 1);
                    buffer->position = buffer->pc;
                }
//                printf("num = %i opcode = %i cycle = %li cursor->pc = %i cycle_to_op = %i\n", buffer->num, buffer->op_code, data->cycle, buffer->pc, buffer->cycle_to_op);
                buffer->op_code = 0;
                buffer->cycle_to_op = 0;
            }
//            printf("num = %i opcode = %i cycle = %li cursor->pc = %i cycle_to_op = %i\n", buffer->num, buffer->op_code, data->cycle, buffer->pc, buffer->cycle_to_op);
            buffer = buffer->next;
            j++;
        }
        if (data->cycle_after_check == data->cycles_to_die || data->cycles_to_die <= 0)
            big_check(data);
        if (data->flag_dump && data->dump_num == i)
        {
            print_buf(data->arena);
            data_free(data);
            run = 0;
        }
        if (data->cursors == NULL)
        {
            data_free(data);
            run = 0;
        }
        // delete
        if (data->cycle == 14763)
            printf("HELOO\n");
    }
    printf("num cycle = %li\n", i);
    printf("winner = %i\n", data->live_player);

    return 0;
}
