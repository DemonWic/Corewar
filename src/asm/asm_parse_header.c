/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:39:16 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:39:17 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

char				*find_no_space_nor_endline(char *start, t_data *data)
{
	char		*current;

	current = start;
	while (ft_isspace(*current) || *current == '\n')
	{
		if (*current == '\n')
		{
			data->eol_flag = 1;
			data->lines++;
		}
		current++;
	}
	return (current);
}

static void			*diag_eof(t_data *data)
{
	data->eof_flag = 1;
	if ((data->is_name == 1) && (data->is_comment == 1))
		return (print_error_init(ERR_NO_DATA_CH, data));
	if ((data->is_name == 0) && (data->is_comment == 0))
		return (print_error_init(ERR_NO_HEADER, data));
	else if (data->is_name == 0)
		return (print_error_init(ERR_NO_NAME_CH, data));
	else if (data->is_comment == 0)
		return (print_error_init(ERR_NO_COMMENT, data));
	else if (data->eol_flag == 0)
		return (print_error_init(ERR_NO_DATA_CH, data));
	return (NULL);
}

static char			*diag_header(t_champ *champ, char *start, t_data *data)
{
	char		*current;

	current = start;
	if (ft_strncmp(current, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		current = check_add_name(current, champ, data, 0);
	else if (ft_strncmp(current, COMMENT_CMD_STRING,\
											ft_strlen(COMMENT_CMD_STRING)) == 0)
		current = check_add_comment(current, champ, data, 0);
	else
		return (print_error_init(ERR_DATA_FORMAT, data));
	return (current);
}

char				*parse_header(t_champ *champ, t_data *data)
{
	char		*current;

	current = data->input;
	while (current && (data->is_name == 0 || data->is_comment == 0))
	{
		current = find_no_space_nor_endline(current, data);
		if (!current)
			return (diag_eof(data));
		else if (*current == '.')
			current = diag_header(champ, current, data);
		else
			return (print_error_init(ERR_DATA_FORMAT, data));
		data->eol_flag = 0;
	}
	if (current && data->eof_flag == 0)
	{
		current = find_no_space_nor_endline(current, data);
		if (*current == '.')
			return (print_error_init(ERR_DATA_FORMAT, data));
		if ((*current == '\0') && data->is_name && data->is_comment)
			return (diag_eof(data));
	}
	data->eol_flag = 0;
	return (current);
}
