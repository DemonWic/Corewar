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
    tab = (char *)ft_memalloc(sizeof(char) * 3);
    if (tab == NULL)
        return (NULL);
//    cursor->op_code = arena[cursor->position];
    if (g_op_tab[cursor->op_code].code_arg == 0)
    {
        tab[0] = 2;
        return (tab);
    }
    else
    {
        arg_code = arena[cor_addr(cursor->position + 1)];
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
    op_code = cursor->op_code;
    if (g_op_tab[op_code].code_arg == 0)  // значит кода аргументов нет
    {
        while (++i < 3)
        {
            if (g_op_tab[op_code].arg_types[i] & T_IND)
                res += IND_SIZE;
            else if (g_op_tab[op_code].arg_types[i] & T_REG)
                res += REG_SIZE;
            else if (g_op_tab[op_code].arg_types[i] & T_DIR)
                res += g_op_tab[op_code].dir;
        }
    }
    else
    {
        res++;
        arg_code = arena[cor_addr(cursor->position + 1)];
        while (++i < 3)
        {
            tab[i] = (arg_code & (192 >> (i * 2))) >> (6 - (i * 2));
            if (tab[i] & 1)
                res += REG_SIZE;
            else if (tab[i] & 2)
                res += g_op_tab[op_code].dir;
            else if (tab[i] & 3)
                res += IND_SIZE;
        }
        // 192 - 1 48 - 2 12 - 3
    }
    return (res);
}