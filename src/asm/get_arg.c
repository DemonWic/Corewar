/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:17:02 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/22 22:47:39 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_arg(char **ptr, t_commands *command, t_champ *champ, int i)
{
	char	*current;

	current = *ptr;
	if (*current == LABEL_CHAR)
	{
		current++;
		if (!(get_label_arg(&current, command, champ->labels, i)))
			return (0);
	}
	else
	{
		if (*current != '-' && !ft_isdigit(*current))
			return (print_error("wrong arg", command->num_line));
		if ((command->args[i] = ft_strtol(current, &current)) < 0 ||
			command->args[i] > 99)
			if (command->arg_types[i] == T_REG)
				return (print_error("Invalid T_REG arg", command->num_line));
		skip_spaces(&current);
		if (!(check_separator(&current, command, i)))
			return (0);
	}
	*ptr = current;
	return (1);
}

void	get_command_size(t_commands *command)
{
	int		i;

	i = 0;
	if (!command->op.code)
		return ;
	command->size++;
	if (command->op.code_arg)
		command->size++;
	while (i < 3)
	{
		if (command->arg_types[i] == T_REG)
			command->size++;
		else if (command->arg_types[i] == T_DIR)
			command->size += command->op.dir;
		else if (command->arg_types[i] == T_IND)
			command->size += 2;
		i++;
	}
}

int		get_args(t_commands *command, t_champ *champ)
{
	int		arg_num;
	int		i;
	char	*ptr;
	int		type;

	arg_num = command->op.arg_num;
	type = 1;
	ptr = command->line;
	i = -1;
	while (++i < 3 && *ptr)
	{
		skip_spaces(&ptr);
		if (skip_new_line(&ptr, NULL))
			break ;
		if (!get_type(&ptr, command, i))
			type = 0;
		if (!(get_arg(&ptr, command, champ, i)))
			return (0);
	}
	if (i != arg_num)
		return (print_error("wrong arg num", command->num_line));
	if (!type)
		return (print_error("type_error", command->num_line));
	get_command_size(command);
	return (1);
}
