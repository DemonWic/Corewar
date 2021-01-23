/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:38:14 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 14:38:15 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_corewar/corewar.h"

void	print_help(void)
{
	ft_putstr("Usage: ./corewar [-a (-dump|-d) <num>] ");
	ft_putstr("[-v] [-n <num>] <champion.cor> <...>\n");
	ft_putstr("-a          : Print output from \"aff\" (Default is off)\n");
	ft_putstr("-dump <num> : Dump memory (32 octets per line)");
	ft_putstr(" after <num> cycles and exit\n");
	ft_putstr("-d    <num> : Dump memory (64 octets per line) ");
	ft_putstr("after <num> cycles and exit\n");
	ft_putstr("-v          : Run visualizer\n");
	ft_putstr("-n    <num> : Set <num> of the next player\n");
	exit(0);
}

int		check_errors(t_init *data, int num)
{
	if (data->error.help)
	{
		print_help();
		return (1);
	}
	if (data->error.invalid_head || data->error.not_valid_file)
	{
		error_invalid_head(data, num);
		return (1);
	}
	if (data->error.large_code)
	{
		error_large_file(data, num);
		return (1);
	}
	return (check_errors2(data, num));
}

void	ft_unmemcpy2(t_init *data, int addr, unsigned char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		data->arena[cor_addr(addr)] = src[i];
		i++;
		addr++;
	}
}

void	*ft_unmemcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
