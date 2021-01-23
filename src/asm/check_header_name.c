/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:41:17 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:41:19 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

static void			*fail_status_name(char *current, t_data *data)
{
	if (*current == '\0')
		data->eof_flag = 1;
	return (print_error_init(ERR_NAME_CH, data));
}

static char			*is_name_and_start_filling(char *current, t_data *data)
{
	data->is_name = 1;
	current++;
	return (current);
}

char				*check_add_name(char *start, t_champ *champ, t_data *data,\
																		int i)
{
	char		*current;

	if (data->is_name == 1)
		return (print_error_init(ERR_DUP_NAME_CH, data));
	current = start + 5;
	while (ft_isspace(*current))
		current++;
	if (*current != '"')
		return (fail_status_name(current, data));
	current = is_name_and_start_filling(current, data);
	while (current && *current != '"' && i <= PROG_NAME_LENGTH)
	{
		champ->name[i] = *current;
		i++;
		if (*current == '\n')
			data->lines++;
		current++;
	}
	if (*current == '\0')
		data->eof_flag = 1;
	if (i >= PROG_NAME_LENGTH)
		return (print_error_init(ERR_LONG_NAME, data));
	if (*current != '"')
		return (print_error_init(ERR_NAME_CH, data));
	return (++current);
}
