/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_coding_to_vm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:31:54 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:32:06 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

int					get_cor_size(t_champ *champ)
{
	int			res;
	int			code_size;
	t_commands	*current;

	res = 4 + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 * 2 + 4;
	code_size = 0;
	if (champ)
		current = champ->commands;
	while (champ && current)
	{
		code_size += current->size;
		current = current->next;
	}
	res += code_size;
	if (champ)
		champ->size = code_size;
	return (code_size);
}

static void			code_header(int fd, t_champ *champ)
{
	code_num_size_fd(COREWAR_EXEC_MAGIC, fd, 4);
	write(fd, champ->name, PROG_NAME_LENGTH);
	code_num_size_fd(0, fd, 4);
	get_cor_size(champ);
	code_num_size_fd(champ->size, fd, 4);
	write(fd, champ->comment, COMMENT_LENGTH);
	code_num_size_fd(0, fd, 4);
}

static char			*get_full_output_filename(char *name_file)
{
	char		*res;

	res = ft_strjoin(name_file, ".cor");
	if (!res)
		return (print_error_init(ERR_NO_NAME, NULL));
	return (res);
}

void				print_success_info(char *file_name)
{
	ft_putstr("\033[33mFile\033[0m ");
	ft_putstr(file_name);
	ft_putendl(" \033[32msuccessfully created\033[0m");
}

char				*all_coding_to_vm(t_champ *champ, t_data *data)
{
	int			fd;
	t_commands	*current;
	char		*file_name;

	file_name = get_full_output_filename(data->name_file);
	if (file_name == NULL)
		return (print_error_init(ERR_NO_NAME, NULL));
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |
															S_IRGRP | S_IROTH);
	if (fd == -1)
		return (print_error_init(ERR_CREATE_FILE, NULL));
	code_header(fd, champ);
	current = champ->commands;
	while (current != NULL)
	{
		code_num_size_fd(current->op.code, fd, 1);
		if (current->op.code_arg == 1)
			code_arg_types(current, fd);
		code_args(current, fd);
		current = current->next;
	}
	close(fd);
	print_success_info(file_name);
	ft_memdel((void **)&file_name);
	return (0);
}
