/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 17:14:56 by ahintz            #+#    #+#             */
/*   Updated: 2018/12/08 17:21:17 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_corewar/corewar.h"

void	validation7(int a[5], char **argv, t_init *data)
{
	data->champs[a[1]]->file = ft_strdup(argv[a[0] + 2]);
	data->champs[a[1]]->num = a[2];
	if (data->nums[a[2]] == 1)
		data->error.help = 1;
	data->nums[a[2]] = 1;
	a[1]++;
	a[0] += 2;
}

int		validation2(int a[5], char **argv, t_init *data)
{
	if (ft_isnumber(argv[a[0] + 1]))
	{
		a[2] = ft_atoi(argv[a[0] + 1]);
		if (a[2] > data->pl_count || a[2] <= 0)
			data->error.help = 1;
		else if (ft_valname(argv[a[0] + 2]))
		{
			data->champs[a[1]] = (t_champ *)ft_memalloc(sizeof(t_champ));
			if (data->champs[a[1]] == NULL)
				return (0);
			validation7(a, argv, data);
		}
		else
		{
			data->error.help = 1;
			return (1);
		}
	}
	else
	{
		data->error.help = 1;
		return (1);
	}
	return (2);
}

int		validation6(int a[5], char **argv, t_init *data)
{
	if (ft_valname(argv[a[0]]))
	{
		if ((a[3] = validation3(a, argv, data)) == 1)
			return (1);
	}
	else if (!ft_strcmp(argv[a[0]], "-n"))
	{
		a[3] = validation2(a, argv, data);
		if (a[3] == 0)
			return (0);
		if (a[3] == 1)
			return (2);
	}
	else if (!ft_strcmp(argv[a[0]], "-dump"))
		validation4(a, argv, data);
	else if (!ft_strcmp(argv[a[0]], "-d"))
		validation5(a, argv, data);
	else if (!ft_strcmp(argv[a[0]], "-v"))
		data->flag_vis = 1;
	else if (!ft_strcmp(argv[a[0]], "-a"))
		data->flag_aff = 1;
	else
		data->error.help = 1;
	return (3);
}

int		validation(int argc, char **argv, t_init *data)
{
	int a[5];

	a[0] = 1;
	a[1] = 0;
	while (a[0] < argc)
	{
		a[4] = validation6(a, argv, data);
		if (a[4] == 0 || a[4] == 1)
			return (a[4]);
		if (a[4] == 2)
			break ;
		a[0]++;
	}
	return (0);
}
