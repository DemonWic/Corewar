/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:08:45 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 12:57:37 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_size(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_exstremum(int n)
{
	char *res;

	if (n == 0)
	{
		res = (char *)malloc(2);
		if (res == NULL)
			return (NULL);
		return (ft_strcpy(res, "0"));
	}
	else
	{
		res = (char *)malloc(12);
		if (res == NULL)
			return (NULL);
		return (ft_strcpy(res, "-2147483648"));
	}
}

char		*ft_itoa(int n)
{
	char	*res;
	int		size;

	size = 0;
	if (n == 0 || n == -2147483648)
		return (ft_exstremum(n));
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	size += ft_size(n);
	res = (char *)malloc(size + 1);
	if (res == NULL)
		return (NULL);
	res[size--] = '\0';
	while (n > 0)
	{
		res[size--] = (n % 10) + 48;
		n /= 10;
	}
	if (size == 0)
		res[size] = '-';
	return (res);
}
