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
    new->num = data->champs[champ]->num;
    new->carry = 0;
    new->position = arena_id;
    new->regs[1] = - data->champs[champ]->num;
    new->next = NULL;
    new->byte_to_next_op = get_byte_to_do(new, data->arena);
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

    sort_champs(data);
    int delta;
    int id;
    delta = MEM_SIZE / data->pl_count;
    i = 0;
    id = 0;
    while (i < data->pl_count)
    {
        id = i * delta;
        ft_unmemcpy(&(data->arena[id]), data->champs[i]->code, (size_t)data->champs[i]->size);
        if (add_cursor(data, i, id))
        {
            data_free(data);
            return(1);
        }
        i++;
    }
//    print_buf(data->arena);
//    i = 0;
//    while (i < 17)
//    {
//        printf("name = %s arg_num = %i code = %i cycles = %i des = %s code_arg = %i dir_size = %i\n", op_tab[i].name, op_tab[i].arg_num, op_tab[i].code, op_tab[i].cycles_to_do, op_tab[i].des, op_tab[i].code_arg, op_tab[i].dir_size);
////        printf("arg_types = %i  %i  %i\n", op_tab[i].arg_types[0], op_tab[i].arg_types[1], op_tab[i].arg_types[2]);
//        i++;
//    }
//    i = 0;
//    while (i < data->pl_count)
//    {
//        printf("Name: \"%s\"  comment: \"%s\" num: %i size: %i code:", data->champs[i]->name, data->champs[i]->comment, data->champs[i]->num, data->champs[i]->size);
//        if (data->champs[i]->code != NULL)
//            printf("yes\n");
//        else
//            printf("no\n");
//        i++;
//    }
    return 0;
}
