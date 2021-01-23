/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:11:25 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/21 14:19:22 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_label_symbols(char *ptr)
{
	int		i;

	i = 0;
	if (!*ptr)
		return (-1);
	while (ptr[i] && ptr[i] != LABEL_CHAR)
	{
		if (!ft_strchr(LABEL_CHARS, ptr[i]))
			return (0);
		i++;
	}
	return (i);
}

int		label_check(char **ptr, t_champ *champ)
{
	int			len;
	char		*current;
	char		*label_name;

	skip_spaces(ptr);
	if (skip_new_line(ptr, champ))
		return (1);
	current = *ptr;
	if (!(len = check_label_symbols(current)))
		return (print_error("wrong line", champ->num_line));
	if (len < 0)
		return (1);
	if (!(label_name = ft_strsub(current, 0, len)))
		return (0);
	current += len;
	if (*current != LABEL_CHAR)
		return (print_error("wrong line or ':' char missed", champ->num_line));
	push_label_back(&champ->labels, label_name, champ->num_line);
	*ptr = current + 1;
	ft_memdel((void**)&label_name);
	if (!(len = get_op(ptr, champ)))
		return (print_error("wrong line", champ->num_line));
	else if (len == 1)
		skip_args(ptr, champ);
	return (1);
}
