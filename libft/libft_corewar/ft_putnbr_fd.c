/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:01:55 by ahintz            #+#    #+#             */
/*   Updated: 2018/11/29 15:55:33 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char s;
	char p;

	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		ft_putnbr_fd((n % 1000000000 * (-1)), fd);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd((-n), fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		s = n % 10 + 48;
		write(fd, &s, 1);
	}
	else
	{
		p = n + 48;
		write(fd, &p, 1);
	}
}
