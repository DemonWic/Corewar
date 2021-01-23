/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:01:19 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 15:01:33 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		valid_read(int argc, char **argv, t_init *data)
{
	pre_valid(argc, argv, data);
	if (data->pl_count > MAX_PLAYERS)
	{
		error_many_champ();
		data_free(data);
		return (1);
	}
	else if (data->error.help == 1)
		return (error_help(data));
	if (validation(argc, argv, data))
		return (1);
	if (data->error.help == 1)
		return (error_help(data));
	cor_num_champ(data);
	if (read_champ(data))
	{
		data_free(data);
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_init *data;

	if (argc < 2)
		print_help();
	if ((data = init_data()) == NULL)
		exit(1);
	if (valid_read(argc, argv, data))
		return (1);
	sort_champs(data);
	if (load_arena(data))
		return (1);
	if (!data->flag_vis)
		pres_champ(data);
	execute(data);
	if (!(data->flag_vis || data->print_win))
		put_winner(data);
	data_free(data);
	return (0);
}
