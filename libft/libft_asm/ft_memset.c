/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:23:38 by loram             #+#    #+#             */
/*   Updated: 2019/09/10 16:45:59 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*data;

	data = (unsigned char *)b;
	while (len-- > 0)
	{
		*data = (unsigned char)c;
		data++;
	}
	return (b);
}
