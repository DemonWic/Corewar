/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_da.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 20:44:06 by loram             #+#    #+#             */
/*   Updated: 2020/01/08 20:44:09 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_del_da(t_da *darr, int *data)
{
	if (darr->id == -1)
		return (0);
	*data = darr->data[darr->id--];
	if (darr->id * 2 < (int)darr->size)
		return (ft_resize_da(darr, darr->size / 2));
	return (-1);
}
