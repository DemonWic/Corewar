/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 09:43:21 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/03 12:31:22 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memory(char **res, char const *s, char c)
{
	int		j;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] != c)
		{
			while (s[i])
			{
				if (s[i + 1] == c || s[i + 1] == '\0')
				{
					res[count] = (char *)malloc(j + 2);
					count++;
					break ;
				}
				i++;
				j++;
			}
		}
		i++;
	}
}

static void	ft_insert(char **res, char const *s, char c)
{
	int		j;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c)
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				res[count][j++] = s[i];
				res[count][j] = '\0';
				count++;
				break ;
			}
			res[count][j++] = s[i++];
		}
		i++;
	}
	res[count] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	res = (char **)malloc(sizeof(char *) * (count + 1));
	if (res == NULL)
		return (NULL);
	ft_memory(res, s, c);
	ft_insert(res, s, c);
	return (res);
}
