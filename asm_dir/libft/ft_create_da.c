/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_da.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:42:59 by loram             #+#    #+#             */
/*   Updated: 2020/01/08 20:43:12 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_da			*ft_create_da(unsigned size)
{
	t_da	*new_da;

	if (!(new_da = (t_da *)malloc(sizeof(t_da))))
		return (NULL);
	new_da->id = 0;
	new_da->size = size;
	if (!size)
		return (new_da);
	if (!(new_da->data = (int *)malloc(sizeof(int) * size)))
	{
		ft_memdel((void **)&new_da);
		return (NULL);
	}
	return (new_da);
}
