//
// Created by Виктор Рыжков on 28.12.2020.
//

#include "corewar.h"

void    op_ld(t_cursor *cursor, t_init *data)
{
    int *types;              // TODO Возможно прописать валидацию типов аргументов согласно таблице !!! обязательно
    int arg1;
    int arg2;

    arg1 = 0;
    arg2 = 0;
    types = get_types_arg(cursor, data->arena);
    cursor->position += 2;
    if (types[0] == DIR_CODE)  // T_DIR
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), op_tab[cursor->op_code].dir);
        cursor->position += op_tab[cursor->op_code].dir;
    }
    else if (types[0] == IND_CODE)
    {
        arg1 = code_to_int(&(data->arena[cursor->position]), IND_SIZE);
        arg1 = code_to_int(&(data->arena[cursor->position + (arg1 % IDX_MOD)]), DIR_SIZE);
        cursor->position += IND_SIZE;
    }
    arg2 = (int)data->arena[cursor->position];
    if (arg2 >= 1 && arg2 <= REG_NUMBER)
    {
        cursor->regs[arg2] = arg1;
        cursor->carry = (arg1 == 0) ? 1 : 0;
    }
    cursor->position += 1;
}