/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:13:19 by loram             #+#    #+#             */
/*   Updated: 2019/09/21 17:03:45 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstdup(t_list *elem)
{
	t_list	*first;
	t_list	*item;

	if (!(item = ft_lst_elemcpy(elem)))
		return (NULL);
	first = item;
	elem = elem->next;
	while (elem)
	{
		if (!(item->next = ft_lst_elemcpy(elem)))
			return (NULL);
		item = item->next;
		elem = elem->next;
	}
	return (first);
}
