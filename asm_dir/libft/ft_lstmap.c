/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:56:59 by loram             #+#    #+#             */
/*   Updated: 2019/09/23 18:57:13 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*flist;

	if (!f || !lst)
		return (NULL);
	flist = f(lst);
	new = flist;
	while (lst->next)
	{
		lst = lst->next;
		if (!(flist->next = f(lst)))
		{
			free(flist->next);
			return (NULL);
		}
		flist = flist->next;
	}
	return (new);
}
