/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:32:25 by loram             #+#    #+#             */
/*   Updated: 2019/09/19 15:03:18 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t		ft_count_parts(char const *s, char c)
{
	size_t		parts;
	size_t		i;

	i = 0;
	parts = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			parts++;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
	}
	return (parts);
}

static char			*ft_get_part(char *s, char c)
{
	char		*start;
	size_t		i;

	start = s;
	i = 0;
	while ((s[i] != '\0') && (s[i] != c))
		i++;
	s[i] = '\0';
	return (ft_strdup(start));
}

static void			ft_free_parts(char **parts, size_t i)
{
	while (i > 0)
	{
		ft_strdel(&(parts[i]));
		i--;
	}
	free(*parts);
}

static char			**ft_get_parts(char *s, char c, size_t parts_num)
{
	char		**parts;
	char		*part;
	size_t		i;
	size_t		j;

	i = 0;
	if ((parts = (char **)ft_memalloc(sizeof(char *) * (parts_num + 1))))
		while (i < parts_num)
		{
			j = 0;
			while (s[j] == c)
				j++;
			if (s[j] != '\0')
				if (!(part = ft_get_part(s + j, c)))
				{
					ft_free_parts(parts, i);
					return (NULL);
				}
			parts[i] = part;
			s = s + j + (ft_strlen(part) + 1);
			i++;
		}
	return (parts);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**parts;
	char		*str;

	if ((s == NULL) || !(str = ft_strdup((char *)s)))
		return (NULL);
	parts = ft_get_parts(str, c, ft_count_parts(str, c));
	free(str);
	return (parts);
}
