/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 18:24:15 by loram             #+#    #+#             */
/*   Updated: 2019/09/13 18:28:14 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] == s2[i]) && (i < n - 1))
	{
		i++;
		if ((s1[i] == '\0') && (s2[i] == '\0'))
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
