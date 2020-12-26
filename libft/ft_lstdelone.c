/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:06:40 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/11 20:02:29 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del) (void *, size_t))
{
	t_list *new_l;

	new_l = *alst;
	if (del)
	{
		del(new_l->content, new_l->content_size);
		free(*alst);
		*alst = NULL;
	}
}
