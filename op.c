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




char *get_types_arg(t_cursor *cursor, unsigned char *arena)
{
//    int tab[3];
    char *tab;
    int arg_code;
    int buf;
    int i;

    i = -1;
//    cursor->op_code = arena[cursor->position];
    tab = (char *)ft_memalloc(sizeof(char) * 3);
    if (g_op_tab[cursor->op_code].code_arg == 0)
        return (tab);
    else
    {
        arg_code = arena[cursor->position + 1];
        while (++i < 3)
        {
            tab[i] = (arg_code & (192 >> (i * 2))) >> (6 - (i * 2));
            buf = tab[i];
        }
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
    if (g_op_tab[op_code].code_arg == 0)  // значит кода аргументов нет
    {
        while (++i < 3)
        {
            if (g_op_tab[op_code].arg_types[i] & T_IND)
                res += T_IND;
            else if (g_op_tab[op_code].arg_types[i] & T_REG)
                res += T_REG;
            else if (g_op_tab[op_code].arg_types[i] & T_DIR)
            {
                if (g_op_tab[op_code].dir_size == 0)
                    res += T_IND;
                else if (g_op_tab[op_code].dir_size == 1)
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
                if (g_op_tab[op_code].dir_size == 0)
                    res += T_IND;
                else if (g_op_tab[op_code].dir_size == 1)
                    res += T_DIR;
            }
            else if (tab[i] & 3)
                res += T_DIR;
        }
        // 192 - 1 48 - 2 12 - 3
    }
    return (res);
}