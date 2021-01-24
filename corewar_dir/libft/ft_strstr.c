/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:41:21 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/03 13:29:57 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	i = -1;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[++i])
	{
		j = 0;
		if (haystack[i] == needle[j])
			while (needle[j])
			{
				if (haystack[i] != needle[j])
				{
					i = i - j;
					break ;
				}
				else if (j == ((int)ft_strlen(needle) - 1))
					return ((char *)&haystack[i - j]);
				i++;
				j++;
			}
	}
	return (NULL);
}
