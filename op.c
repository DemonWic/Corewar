/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "op.h"
#include "corewar.h"
typedef struct s_op
{
    char *name;
    int  arg_num;
    int  arg_types[3];
    int  code;
    int  cycles_to_do;
    char *des;
    int code_arg;  // true / false есть ли тип аргументов или нет
    int dir_size; // if 0 - 4 byte if 1 - 2 byte
}               t_op;

t_op    op_tab[17] =
{
        {0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};



int *get_types_arg(t_cursor *cursor, unsigned char *arena)
{
    int tab[3];
    int op_code;
    int arg_code;
    int i;

    i = -1;
    op_code = arena[cursor->position];
    if (op_tab[op_code].code_arg == 0)
        return (tab);
    else
    {
        arg_code = arena[cursor->position + 1];
        while (++i < 3)
            tab[i] = (arg_code & (192 >> (i * 2))) >> (6 - (i * 2));
    }
    return (tab);
}

int    get_byte_to_do(t_cursor *cursor, unsigned char *arena)
{
    int op_code;
    int arg_code;
    int i;
    int res;
    int tab[3];

    i = -1;
    res = 1;
    op_code = arena[cursor->position];
    if (op_tab[op_code].code_arg == 0)  // значит кода аргументов нет
    {
        while (++i < 3)
        {
            if (op_tab[op_code].arg_types[i] & T_IND)
                res += T_IND;
            else if (op_tab[op_code].arg_types[i] & T_REG)
                res += T_REG;
            else if (op_tab[op_code].arg_types[i] & T_DIR)
            {
                if (op_tab[op_code].dir_size == 0)
                    res += T_IND;
                else if (op_tab[op_code].dir_size == 1)
                    res += T_DIR;
            }
        }
    }
    else
    {
        res++;
        arg_code = arena[cursor->position + 1];
        while (++i < 3)
        {
            tab[i] = (arg_code & (192 >> (i * 2))) >> (6 - (i * 2));
            if (tab[i] & 1)
                res += T_REG;
            else if (tab[i] & 2)
            {
                if (op_tab[op_code].dir_size == 0)
                    res += T_IND;
                else if (op_tab[op_code].dir_size == 1)
                    res += T_DIR;
            }
            else if (tab[i] & 3)
                res += T_DIR;
        }
        // 192 - 1 48 - 2 12 - 3
    }
    return (res);
}