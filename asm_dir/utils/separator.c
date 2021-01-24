/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:14:44 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 12:04:29 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_separator(char **ptr, t_commands *command, int i)
{
	if (**ptr == SEPARATOR_CHAR)
	{
		if (i == command->op.arg_num - 1)
			return (print_error("separator after last arg or too many args",
								command->num_line));
			*ptr += 1;
	}
	else if (i < command->op.arg_num - 1)
		return (print_error("separator missed", command->num_line));
	else
	{
		skip_spaces(ptr);
		if (**ptr != '\n')
			return (print_error("wrong data after last arg",
								command->num_line));
	}
	return (1);
}
