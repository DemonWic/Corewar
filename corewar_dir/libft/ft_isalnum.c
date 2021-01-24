/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 14:58:55 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/01 16:27:19 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	int	ups;
	int	los;
	int	num;
	int	i;

	ups = (int)'A';
	los = (int)'a';
	num = (int)'0';
	i = 0;
	while (i++ < 26)
		if (c == ups++ || c == los++)
			return (1);
	i = 0;
	while (i++ <= 9)
		if (c == num++)
			return (1);
	return (0);
}
