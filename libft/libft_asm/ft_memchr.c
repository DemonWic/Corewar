/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:44:36 by loram             #+#    #+#             */
/*   Updated: 2019/09/22 21:14:30 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	sym;

	str = (unsigned char *)s;
	sym = (unsigned char)c;
	i = 0;
	while ((n - i) > 0)
		if (str[i] == sym)
			return (&str[i]);
		else
			i++;
	return (NULL);
}
