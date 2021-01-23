/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:56:30 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 11:54:13 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_arg_type(int type, t_commands *command, int i)
{
	int		tmp;

	tmp = command->op.arg_types[i];
	if (tmp == 1 && type == T_REG)
		return (1);
	if (tmp == 2 && type == T_DIR)
		return (1);
	if (tmp == 3 && (type == T_REG || type == T_DIR))
		return (1);
	if (tmp == 4 && type == T_IND)
		return (1);
	if (tmp == 5 && (type == T_REG || type == T_IND))
		return (1);
	if (tmp == 6 && (type == T_DIR || type == T_IND))
		return (1);
	if (tmp == 7 && (type == T_REG || type == T_DIR || type == T_IND))
		return (1);
	return (0);
}

int		get_type(char **ptr, t_commands *command, int i)
{
	t_arg_type	type;
	char		*current;

	current = *ptr;
	if (*current == 'r')
		type = T_REG;
	else if (*current == '%')
		type = T_DIR;
	else
		type = T_IND;
	if (!check_arg_type(type, command, i))
		return (0);
	command->arg_types[i] = type;
	if (type != T_IND)
		current++;
	*ptr = current;
	return (1);
}
