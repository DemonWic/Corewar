/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:23:12 by loram             #+#    #+#             */
/*   Updated: 2019/09/18 17:29:44 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*res;
	size_t	i;
	size_t	start;
	size_t	fin;

	if (s == NULL)
		return (NULL);
	start = 0;
	fin = ft_strlen(s);
	while (ft_istabeolsp(s[start]))
		start++;
	while ((fin > start) && ft_istabeolsp(s[fin - 1]))
		fin--;
	if ((res = ft_strnew((fin > start) ? (fin - start) : 0)))
	{
		i = 0;
		while (start < fin)
		{
			res[i] = s[start];
			i++;
			start++;
		}
	}
	return (res);
}
