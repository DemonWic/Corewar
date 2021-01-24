/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:48:01 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:48:02 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

static void			comments_to_spaces(t_data *data)
{
	int		qmarks_flasher;
	char	*current;

	qmarks_flasher = 0;
	current = data->input;
	while (*current)
	{
		if (*current == '"')
			qmarks_flasher ^= 1;
		if (!qmarks_flasher &&\
					(*current == COMMENT_CHAR || *current == ALT_COMMENT_CHAR))
		{
			while (*current && *current != '\n')
			{
				*current = ' ';
				current++;
			}
		}
		current++;
	}
}

static int			error_open_file(char *file, t_data *data)
{
	print_error_init(ERR_NO_FILE, data);
	ft_putstr_fd(" \033[31m- \033[0m", 2);
	ft_putendl_fd(file, 2);
	return (0);
}

static void			parse_champ_and_code(char *current, t_champ *champ,
																t_data *data)
{
	champ->num_line = data->lines;
	if (parse_code_part(current, champ))
		all_coding_to_vm(champ, data);
	else
	{
		ft_putstr_fd(data->name_file, 2);
		ft_putendl_fd(".s", 2);
	}
}

int					parse_asm(char *file)
{
	int			fd;
	t_champ		*champ;
	char		*current;
	t_data		*data;

	fd = open(file, O_RDONLY);
	if (fd < 0 || read(fd, &fd, 0) < 0)
		return (error_open_file(file, NULL));
	data = get_asm_data(file);
	if (data)
	{
		comments_to_spaces(data);
		champ = init_champ();
		if (champ)
		{
			current = parse_header(champ, data);
			if (current && data->eof_flag == 0)
				parse_champ_and_code(current, champ, data);
			clean_champ(champ);
		}
		clean_data(data);
	}
	return (0);
}
