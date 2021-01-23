/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 02:40:33 by loram             #+#    #+#             */
/*   Updated: 2021/01/14 02:40:34 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_errors.h"

static void		*fail_status_comment(char *current, t_data *data)
{
	if (*current == '\0')
		data->eof_flag = 1;
	return (print_error_init(ERR_COMMENT, data));
}

static char		*is_comment_and_start_filling(char *current, t_data *data)
{
	data->is_comment = 1;
	current++;
	return (current);
}

char			*check_add_comment(char *start, t_champ *champ, t_data *data,\
																		int i)
{
	char	*current;

	if (data->is_comment == 1)
		return (print_error_init(ERR_DUP_COMMENT, data));
	current = start + 8;
	while (ft_isspace(*current))
		current++;
	if (*current != '"')
		return (fail_status_comment(current, data));
	current = is_comment_and_start_filling(current, data);
	while (current && *current != '"' && i <= COMMENT_LENGTH)
	{
		champ->comment[i] = *current;
		i++;
		if (*current == '\n')
			data->lines++;
		current++;
	}
	if (*current == '\0')
		data->eof_flag = 1;
	if (i >= COMMENT_LENGTH)
		return (print_error_init(ERR_LONG_COMMENT, data));
	if (*current != '"')
		return (print_error_init(ERR_COMMENT, data));
	return (++current);
}
