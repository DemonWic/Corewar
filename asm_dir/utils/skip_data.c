/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:49:25 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/17 11:50:35 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	skip_spaces(char **ptr)
{
	char	*current;

	current = *ptr;
	if (*current == '\0')
		return ;
	while (*current == ' ' | *current == '\t')
		current++;
	*ptr = current;
}

int		skip_new_line(char **ptr, t_champ *champ)
{
	if (**ptr != '\n')
		return (0);
	*ptr += 1;
	if (champ)
		champ->num_line++;
	return (1);
}

void	skip_args(char **ptr, t_champ *champ)
{
	char	*current;

	current = *ptr;
	while (current && *current != '\n')
		current++;
	champ->num_line++;
	current++;
	*ptr = current;
}
