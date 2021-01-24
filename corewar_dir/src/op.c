/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by ahintz            #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char	*get_types_arg(t_cursor *cursor, unsigned char *arena)
{
	char	*tab;
	int		arg_code;
	int		i;

	i = -1;
	tab = (char *)ft_memalloc(sizeof(char) * 3);
	if (tab == NULL)
		return (NULL);
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
		}
	}
	return (tab);
}

void	ft_curdel(t_cursor *cursor)
{
	t_cursor	*buffer;
	t_cursor	*del;

	buffer = cursor;
	while (buffer)
	{
		del = buffer;
		buffer = buffer->next;
		ft_memdel((void **)&del);
	}
}
