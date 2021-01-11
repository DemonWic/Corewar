//
// Created by Виктор Рыжков on 28.12.2020.
//

#include "corewar.h"

int   op_ld(t_cursor *cursor, t_init *data)
{
    char *types;              // TODO Возможно прописать валидацию типов аргументов согласно таблице !!! обязательно
    int arg1;
    int arg2;

    arg1 = 0;
    arg2 = 0;
    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    if (types[0] == DIR_CODE)  // T_DIR
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir);
        cursor->position += g_op_tab[cursor->op_code].dir;
    }
    else if (types[0] == IND_CODE)
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), IND_SIZE);
        arg1 = code_to_int(&(data->arena[cursor->pc + (arg1 % IDX_MOD)]), 4);
        cursor->position += IND_SIZE;
    }
    arg2 = (int)data->arena[cursor->position];
    if (arg2 >= 1 && arg2 <= REG_NUMBER)
    {
        cursor->regs[arg2] = arg1;
        cursor->carry = (arg1 == 0) ? 1 : 0;
    }
    cursor->position += 1;
    cursor->pc = cursor->position;
    return (0);
}

int op_st(t_cursor *cursor, t_init *data)
{
    char *types;
    unsigned char *num;
    int arg1;
    int arg2;

    arg1 = 0;
    arg2 = 0;
    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    arg1 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if (types[1] == REG_CODE)
    {
        arg2 = (int)data->arena[cursor->position];
        cursor->position += 1;
        if ((arg1 >= 1 && arg1 <= REG_NUMBER) && (arg2 >= 1 && arg2 <= REG_NUMBER))
        {
            cursor->regs[arg2] = cursor->regs[arg1];
            cursor->carry = (cursor->regs[arg1] == 0) ? 1 : 0;
        }
    }
    else if (types[1] == IND_CODE)
    {
        arg2 = code_to_int(&(data->arena[cursor->position]), IND_SIZE) % IDX_MOD;
        cursor->position += IND_SIZE;
        // TODO int -> unsigned char
        num = int_to_code(cursor->regs[arg1]);
        ft_color(&(data->col_arena[cursor->pc + arg2]), REG_SIZE, (cursor->regs[1] * -1));
        ft_unmemcpy(&(data->arena[cursor->pc + arg2]), num, REG_SIZE);
        free(num);
    }
    free(types);
    return (0);
}

int op_add(t_cursor *cursor, t_init *data)
{
    int arg1;
    int arg2;
    int arg3;

    arg1 = 0;
    arg2 = 0;
    arg3 = 0;
    cursor->position += 2;
    arg1 = (int)data->arena[cursor->position];
    cursor->position += 1;
    arg2 = (int)data->arena[cursor->position];
    cursor->position += 1;
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if ((arg1 >= 1 && arg1 <= REG_NUMBER) && (arg2 >= 1 && arg2 <= REG_NUMBER) && (arg3 >= 1 && arg3 <= REG_NUMBER))
    {
        cursor->regs[arg3] = cursor->regs[arg1] + cursor->regs[arg2];
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
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
    arg1 = (int)data->arena[cursor->position];
    cursor->position += 1;
    arg2 = (int)data->arena[cursor->position];
    cursor->position += 1;
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if ((arg1 >= 1 && arg1 <= REG_NUMBER) && (arg2 >= 1 && arg2 <= REG_NUMBER) && (arg3 >= 1 && arg3 <= REG_NUMBER))
    {
        cursor->regs[arg3] = cursor->regs[arg1] - cursor->regs[arg2];
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
    }
    return (0);
}

int get_value(int type, t_cursor *cursor, t_init *data)
{
    int arg1;

    if (type == REG_CODE)
    {
        arg1 = (int)data->arena[cursor->position];
        if (arg1 >= 1 && arg1 <= REG_NUMBER)
            arg1 = cursor->regs[arg1];
        cursor->position += 1;
    }
    else if (type == IND_CODE)
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), IND_SIZE) % IDX_MOD;
        arg1 = code_to_int(&(data->arena[cursor->pc + arg1]), 4);
        cursor->position += IND_SIZE;
    }
    else if (type == DIR_CODE)
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir);
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
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if (arg3 >= 1 && arg3 <= REG_NUMBER)
    {
        cursor->regs[arg3] = arg1 & arg2;
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
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
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if (arg3 >= 1 && arg3 <= REG_NUMBER)
    {
        cursor->regs[arg3] = arg1 | arg2;
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
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
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if (arg3 >= 1 && arg3 <= REG_NUMBER)
    {
        cursor->regs[arg3] = arg1 ^ arg2;
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
    }
    return (0);
}


int op_zjmp(t_cursor *cursor, t_init *data)
{
    int arg1;

    cursor->position += 1;
    arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir) % IDX_MOD;
    if (cursor->carry == 1)
    {
        cursor->pc += arg1;
        cursor->position = cursor->pc;
    }
    else
    {
        cursor->position += g_op_tab[cursor->op_code].dir;
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
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if (arg3 >= 1 && arg3 <= REG_NUMBER)
    {
        cursor->regs[arg3] = code_to_int(&(data->arena[cursor->pc + ((arg1 + arg2) % IDX_MOD)]), 4);
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
    }
    cursor->pc = cursor->position;
    return (0);
}

int op_sti(t_cursor *cursor, t_init *data)
{
    char *types;
    unsigned char *num;
    int arg1;
    int arg2;
    int arg3;

    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    arg1 = (int)data->arena[cursor->position];
    cursor->position += 1;
    arg2 = get_value(types[1], cursor, data);
    arg3 = get_value(types[2], cursor, data);
    if (arg1 >= 1 && arg1 <= REG_NUMBER)
    {
        num = int_to_code(cursor->regs[arg1]);
        ft_color(&(data->col_arena[cursor->pc + ((arg2 + arg3) % IDX_MOD)]), REG_SIZE, (cursor->regs[1] * -1));
        ft_unmemcpy(&(data->arena[cursor->pc + ((arg2 + arg3) % IDX_MOD)]), num, REG_SIZE);
        free(num);
    }
    cursor->pc = cursor->position;
    free(types);
    return (0);
}

int op_fork(t_cursor *cursor, t_init *data)
{
    int arg1;
    int i;
    t_cursor *new;
    t_cursor *buf;

    i = -1;
    cursor->position += 1;
    arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir) % IDX_MOD;
    cursor->position += g_op_tab[cursor->op_code].dir;
    cursor->pc = cursor->position;
    new = (t_cursor *)ft_memalloc(sizeof(t_cursor));
    if (new == NULL)
        return (1);
    new->cycle_num_live = cursor->cycle_num_live;
    new->carry = cursor->carry;
    new->num = cursor->num;
    while (++i <= REG_NUMBER)
        new->regs[i] = cursor->regs[i];
    new->position = arg1;
    new->pc = arg1;
    if (data->cursors == NULL)
    {
        data->cursors = new;
        data->cursors_count++;
    }
    else
    {
        buf = data->cursors;
        new->next = buf;
        data->cursors = new;
        data->cursors_count++;
    }
    return (0);
}

int    op_lld(t_cursor *cursor, t_init *data)
{
    char *types;              // TODO Возможно прописать валидацию типов аргументов согласно таблице !!! обязательно
    int arg1;
    int arg2;

    arg1 = 0;
    arg2 = 0;
    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    if (types[0] == DIR_CODE)  // T_DIR
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir);
        cursor->position += g_op_tab[cursor->op_code].dir;
    }
    else if (types[0] == IND_CODE)
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), IND_SIZE);
        arg1 = code_to_int(&(data->arena[cursor->pc + arg1]), 4);
        cursor->position += IND_SIZE;
    }
    arg2 = (int)data->arena[cursor->position];
    if (arg2 >= 1 && arg2 <= REG_NUMBER)
    {
        cursor->regs[arg2] = arg1;
        cursor->carry = (arg1 == 0) ? 1 : 0;
    }
    cursor->position += 1;
    cursor->pc = cursor->position;
    return (0);
}

int op_lldi(t_cursor *cursor, t_init *data)
{
    char *types;
    int arg1;
    int arg2;
    int arg3;

    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    arg1 = get_value(types[0], cursor, data);
    arg2 = get_value(types[1], cursor, data);
    arg3 = (int)data->arena[cursor->position];
    cursor->position += 1;
    if (arg3 >= 1 && arg3 <= REG_NUMBER)
    {
        cursor->regs[arg3] = code_to_int(&(data->arena[cursor->pc + (arg1 + arg2)]), 4);
        cursor->carry = (cursor->regs[arg3] == 0) ? 1 : 0;
    }
    cursor->pc = cursor->position;
    return (0);
}

int op_lfork(t_cursor *cursor, t_init *data)
{
    int arg1;
    int i;
    t_cursor *new;
    t_cursor *buf;

    i = -1;
    cursor->position += 1;
    arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir);
    cursor->position += g_op_tab[cursor->op_code].dir;
    cursor->pc = cursor->position;
    new = (t_cursor *)ft_memalloc(sizeof(t_cursor));
    if (new == NULL)
        return (1);
    new->cycle_num_live = cursor->cycle_num_live;
    new->carry = cursor->carry;
    new->num = cursor->num;
    while (++i <= REG_NUMBER)
        new->regs[i] = cursor->regs[i];
    new->position = arg1;
    new->pc = arg1;
    if (data->cursors == NULL)
    {
        data->cursors = new;
        data->cursors_count++;
    }
    else
    {
        buf = data->cursors;
        new->next = buf;
        data->cursors = new;
        data->cursors_count++;
    }
    return (0);
}

int op_aff(t_cursor *cursor, t_init *data)
{
    char *types;
    int arg1;
    char sym;

    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    arg1 = (int)data->arena[cursor->position];
    cursor->position += 1;
    cursor->pc = cursor->position;
    if ((arg1 >= 1 && arg1 <= REG_NUMBER) && data->flag_aff)
    {
        sym = (char)cursor->regs[arg1];
        ft_putstr("Aff: ");
        ft_putchar(sym);
        ft_putchar('\n');
    }
    return (0);
}

int op_live(t_cursor *cursor, t_init *data)
{
    int arg1;

    cursor->cycle_num_live = data->cycle;
    cursor->position += 1;
    arg1 = code_to_int(&(data->arena[cursor->position]), g_op_tab[cursor->op_code].dir);
    cursor->position += g_op_tab[cursor->op_code].dir;
    arg1 = - arg1;
    if (arg1 >= 1 && arg1 <= data->pl_count)
    {
        data->live_player = arg1;
        data->live_count++;
    }
    cursor->pc = cursor->position;
    return (0);
}