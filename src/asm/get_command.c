/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:47:23 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 12:18:06 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_max(int a, int b)
{
	return (a >= b ? a : b);
}

int		find_command_len(char *ptr)
{
	int		i;

	i = 0;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' ||
			*ptr == LABEL_CHAR || *ptr == '%')
			return (i);
		i++;
		ptr++;
	}
	return (i);
}

int		find_line_len(char *ptr)
{
	int		i;

	i = 0;
	while (*ptr && *ptr != '\n')
	{
		i++;
		ptr++;
	}
	return (i);
}

int		get_op(char **ptr, t_champ *champ)
{
	int		i;
	char	*current;
	int		len;

	i = 17;
	skip_spaces(ptr);
	if (skip_new_line(ptr, champ))
		return (2);
	current = *ptr;
	while (--i > 0)
	{
		len = ft_max(find_command_len(*ptr), ft_strlen(g_op_tab[i].name));
		if (ft_strnequ(current, g_op_tab[i].name, len) && current[len] != ':')
		{
			champ->current_command = push_command_back(&champ->commands,
									g_op_tab[i]);
			champ->current_command->num_line = champ->num_line;
			current += ft_strlen(g_op_tab[i].name);
			champ->current_command->line = ft_strsub(current, 0,
							find_line_len(current) + 1);
			*ptr = current;
			return (1);
		}
	}
	return (0);
}
