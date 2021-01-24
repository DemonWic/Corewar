/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:56:20 by loram             #+#    #+#             */
/*   Updated: 2019/09/17 23:19:04 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	if ((s1 == NULL) || (s2 == NULL))
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_strnew(len);
	if (str == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (len >= i)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str);
}
