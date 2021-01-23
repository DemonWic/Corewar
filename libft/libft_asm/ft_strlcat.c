/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 22:50:19 by loram             #+#    #+#             */
/*   Updated: 2019/09/12 23:44:08 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	len;

	len = ft_strlen(dst);
	if (size > len)
		ft_strncat(dst, src, (size - len - 1));
	if (size < len)
		return (size + ft_strlen(src));
	return (len + ft_strlen(src));
}
