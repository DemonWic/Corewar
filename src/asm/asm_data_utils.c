/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 02:01:31 by loram             #+#    #+#             */
/*   Updated: 2021/01/19 12:28:48 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

void				clean_champ(t_champ *champ)
{
	int			i;

	champ->num = 0;
	champ->size = 0;
	champ->num_line = 0;
	i = 0;
	while (i < PROG_NAME_LENGTH + 1)
	{
		champ->name[i] = '\0';
		i++;
	}
	i = 0;
	while (i < COMMENT_LENGTH + 1)
	{
		champ->comment[i] = '\0';
		i++;
	}
	free_commands_list(&champ->commands);
	free_labels_list(&champ->labels);
	ft_memdel((void **)&champ);
}

void				clean_data(t_data *data)
{
	data->data_size = 0;
	data->lines = 0;
	data->is_comment = 0;
	data->is_name = 0;
	ft_memdel((void **)&data->name_file);
	ft_memdel((void **)&data->input);
	ft_memdel((void **)&data);
}

void				*print_error_init(char *err_str, t_data *data)
{
	if (data != NULL)
	{
		ft_putstr_fd("\033[33mline ", 2);
		ft_putnbr_fd(data->lines + 1, 2);
		ft_putstr_fd(": \033[0m", 2);
	}
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(err_str, 2);
	if (data != NULL)
	{
		ft_putstr_fd(" \033[33m-\033[0m ", 2);
		ft_putstr_fd(data->name_file, 2);
		ft_putstr_fd(".s\n", 2);
	}
	ft_putstr_fd("\033[0m", 2);
	if (data != NULL)
		data->eof_flag = 2;
	return (NULL);
}

t_data				*init_asm_data(void)
{
	t_data		*data;

	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		return (print_error_init(ERR_DATA_INIT, NULL));
	else
		return (data);
}

int					print_error(char *ptr, int line)
{
	ft_putstr_fd("\033[33mline ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(": \033[31mERROR: ", 2);
	write(2, ptr, ft_strlen(ptr));
	ft_putstr_fd("\033[33m - \033[0m", 2);
	return (0);
}
