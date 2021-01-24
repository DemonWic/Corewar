/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loram <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:08:22 by loram             #+#    #+#             */
/*   Updated: 2019/09/19 19:29:43 by loram            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_numlen_sign(int n)
{
	int		len;
	int		minus;

	if (n == 0)
		return (1);
	len = 0;
	minus = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len + minus);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		numlen;
	int		digit;

	numlen = ft_numlen_sign(n);
	if ((str = ft_strnew(numlen)))
	{
		if (n == 0)
			str[0] = '0';
		else
			while (numlen-- > 0)
			{
				if (n == 0)
				{
					str[0] = '-';
				}
				else
				{
					digit = n % 10;
					str[numlen] = ((digit < 0) ? -digit : digit) + '0';
					n = n / 10;
				}
			}
	}
	return (str);
}
