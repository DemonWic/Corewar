/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:44:44 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 11:53:13 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			get_arg_data(t_champ *champ)
{
	t_commands	*command;

	command = champ->commands;
	while (command)
	{
		if (!get_args(command, champ))
			return (0);
		command = command->next;
	}
	command = champ->commands;
	while (command)
	{
		convert_label_to_number(command, champ);
		command = command->next;
	}
	return (1);
}

int			check_last_line(char *ptr, t_champ *champ)
{
	t_labels	*label;

	label = champ->labels;
	while (label && label->next)
		label = label->next;
	if ((label && champ->num_line == label->num_line) ||
		champ->num_line == champ->current_command->num_line)
		if (*(ptr - 1) != '\n')
			return (0);
	return (1);
}

int			parse_code_part(char *ptr, t_champ *champ)
{
	int		op;

	champ->num_line++;
	while (ptr && *ptr)
	{
		op = get_op(&ptr, champ);
		if (op == 1)
			skip_args(&ptr, champ);
		if (op == 2)
			continue ;
		if (!op)
			if (!label_check(&ptr, champ))
				return (0);
	}
	if (!(check_last_line(ptr, champ)))
		return (print_error("\\n missed", champ->num_line));
	return (get_arg_data(champ));
}
