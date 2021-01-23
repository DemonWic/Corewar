/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_to_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:12:46 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 11:59:17 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_number(int arg_line, int label_line, t_commands *commands)
{
	int		number;

	number = 0;
	if (arg_line > label_line)
	{
		while (commands)
		{
			if (commands->num_line >= label_line &&
				commands->num_line < arg_line)
				number -= commands->size;
			commands = commands->next;
		}
	}
	else
	{
		while (commands)
		{
			if (commands->num_line >= arg_line &&
				commands->num_line < label_line)
				number += commands->size;
			commands = commands->next;
		}
	}
	return (number);
}

void	convert_label_to_number(t_commands *command, t_champ *champ)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (command->label_arg[i])
			command->args[i] = get_number(command->num_line,
			command->label_arg[i], champ->commands);
		i++;
	}
}
