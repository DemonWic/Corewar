/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:27:51 by loram             #+#    #+#             */
/*   Updated: 2019/09/21 18:16:19 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memrealloc(void *src, size_t new_size, size_t old_size)
{
	void	*new;

	if (!new_size)
		return (NULL);
	if (!src)
		return (ft_memalloc(new_size));
	if (!(new = ft_memalloc(new_size)))
		return (NULL);
	ft_memmove(new, src, old_size);
	free(src);
	return (new);
}
