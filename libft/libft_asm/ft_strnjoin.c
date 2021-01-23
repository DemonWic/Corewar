/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:28:16 by loram             #+#    #+#             */
/*   Updated: 2019/10/24 19:24:09 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*str;
	size_t	n;

	if ((!s2) || (ft_strlen(s2) < len))
		return (NULL);
	if (!s1)
		return (ft_strsub(s2, 0, len));
	if ((str = ft_strnew(ft_strlen(s1) + len)))
	{
		n = 0;
		while (*s1)
			str[n++] = *s1++;
		while (len--)
			str[n++] = *s2++;
		str[n] = '\0';
		return (str);
	}
	return (NULL);
}
