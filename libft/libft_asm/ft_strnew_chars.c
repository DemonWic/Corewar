/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:49:41 by loram             #+#    #+#             */
/*   Updated: 2020/02/13 21:49:44 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_chars(size_t size, char c)
{
	char	*s;

	if (size > size + 1)
		return (NULL);
	if (!(s = (char *)ft_memalloc_chars((size + 1), c)))
		return (NULL);
	else
		return (s);
}
