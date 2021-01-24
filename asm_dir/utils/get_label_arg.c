/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:16:01 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 17:43:43 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*find_label_end(char *ptr)
{
	while (*ptr)
	{
		if (*ptr == SEPARATOR_CHAR ||
			*ptr == ' ' ||
			*ptr == '\t' ||
			*ptr == '\n')
			return (ptr);
		ptr++;
	}
	return (0);
}

int		get_label_arg(char **ptr, t_commands *command, t_labels *label, int i)
{
	char		*end;
	char		*label_name;
	int			label_len;

	if (!(end = find_label_end(*ptr)))
		return (0);
	label_len = end - *ptr;
	if (!(label_name = ft_strsub(*ptr, 0, label_len)))
		return (0);
	while (label)
	{
		if (ft_strequ(label_name, label->label_name))
		{
			command->label_arg[i] = label->num_line;
			*ptr += label_len;
			skip_spaces(ptr);
			ft_memdel((void**)&label_name);
			if (!(check_separator(ptr, command, i)))
				return (0);
			return (1);
		}
		label = label->next;
	}
	ft_memdel((void**)&label_name);
	return (print_error("label arg doesn't exist", command->num_line));
}
