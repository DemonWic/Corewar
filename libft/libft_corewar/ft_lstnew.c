/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:47:47 by ahintz            #+#    #+#             */
/*   Updated: 2019/02/02 19:00:27 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content_size)
{
	t_list *new_l;

	new_l = (t_list *)malloc(sizeof(t_list));
	if (new_l == NULL)
		return (NULL);
	new_l->content = NULL;
	new_l->content_size = content_size;
	new_l->next = NULL;
	return (new_l);
}
