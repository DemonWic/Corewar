/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:53:58 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 11:56:19 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_commands		*create_command_elem(t_op op)
{
	t_commands	*elem;

	if (!(elem = (t_commands*)ft_memalloc(sizeof(t_commands))))
		return (NULL);
	elem->op = op;
	return (elem);
}

t_commands		*push_command_back(t_commands **head, t_op op)
{
	t_commands	*current;

	if (!*head)
	{
		if (!(*head = create_command_elem(op)))
			return (NULL);
		current = *head;
		return (current);
	}
	current = *head;
	while (current->next)
		current = current->next;
	if (!(current->next = create_command_elem(op)))
	{
		free_commands_list(head);
		return (NULL);
	}
	return (current->next);
}

void			free_commands_list(t_commands **head)
{
	t_commands	*command;

	if (!head)
		return ;
	while (*head)
	{
		command = *head;
		*head = (*head)->next;
		ft_memdel((void**)&command->line);
		command->next = NULL;
		ft_memdel((void**)&command);
	}
}
