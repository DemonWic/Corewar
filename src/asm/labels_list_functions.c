/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels_list_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <bsausage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:55:19 by bsausage          #+#    #+#             */
/*   Updated: 2021/01/19 11:57:06 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_labels		*create_label_elem(char *label_name, int num_line)
{
	t_labels	*elem;

	if (!(elem = (t_labels*)ft_memalloc(sizeof(t_labels))))
		return (NULL);
	if (!(elem->label_name = ft_strdup(label_name)))
	{
		ft_memdel((void**)&elem);
		return (NULL);
	}
	elem->num_line = num_line;
	return (elem);
}

t_labels		*push_label_back(t_labels **head,
					char *label_name, int num_line)
{
	t_labels	*current;

	if (!*head)
	{
		if (!(*head = create_label_elem(label_name, num_line)))
			return (NULL);
		current = *head;
		return (current);
	}
	current = *head;
	while (current->next)
		current = current->next;
	if (!(current->next = create_label_elem(label_name, num_line)))
	{
		free_labels_list(head);
		return (NULL);
	}
	return (current->next);
}

void			free_labels_list(t_labels **head)
{
	t_labels	*label;

	if (!head)
		return ;
	while (*head)
	{
		label = *head;
		*head = (*head)->next;
		ft_memdel((void**)&label->label_name);
		label->next = NULL;
		ft_memdel((void**)&label);
	}
}
