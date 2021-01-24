/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_args_and_types.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:42:18 by loram             #+#    #+#             */
/*   Updated: 2021/01/19 11:51:52 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

void				code_args(t_commands *command, int fd)
{
	int			i;

	i = 0;
	while (i < command->op.arg_num)
	{
		if (command->arg_types[i] == 2)
			code_num_size_fd(command->args[i], fd, command->op.dir);
		else if (command->arg_types[i] == 1)
			code_num_size_fd(command->args[i], fd, 1);
		else if (command->arg_types[i] == 3)
			code_num_size_fd(command->args[i], fd, 2);
		else
			print_error_init(ERR_INVALID_ARGUMENT, NULL);
		i++;
	}
}

void				code_arg_types(t_commands *command, int fd)
{
	int			num;
	int			*arg_types;
	int			i;

	num = 0;
	arg_types = command->arg_types;
	i = 0;
	while (i < 3)
	{
		if (arg_types[i] == 4)
			arg_types[i] = 3;
		i++;
	}
	num += (arg_types[0] / 10 * 128) + (arg_types[0] % 10 * 64);
	num += (arg_types[1] / 10 * 32) + (arg_types[1] % 10 * 16);
	num += (arg_types[2] / 10 * 8) + (arg_types[2] % 10 * 4);
	code_num_size_fd(num, fd, 1);
}
