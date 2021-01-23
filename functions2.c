/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahintz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:46:36 by ahintz            #+#    #+#             */
/*   Updated: 2021/01/23 14:46:38 by ahintz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_isnumber(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_valname(char *file)
{
	int i;
	int len;

	if (file == NULL)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	i = len - 4;
	len = ft_strcmp(&file[i], ".cor");
	if (len == 0)
		return (1);
	return (0);
}

t_init	*init_data(void)
{
	t_init *data;

	data = (t_init *)ft_memalloc(sizeof(t_init));
	if (data == NULL)
		return (NULL);
	data->num = 0;
	data->cursor_num = 0;
	data->flag_n = 0;
	data->flag_dump = 0;
	data->flag_aff = 0;
	data->flag_vis = 0;
	data->pl_count = 0;
	data->print_win = 0;
	data->invalid = 0;
	data->error.help = 0;
	data->error.invalid_head = 0;
	data->error.not_valid_file = 0;
	data->error.too_many_files = 0;
	data->error.large_code = 0;
	data->champs = (t_champ **)ft_memalloc((sizeof(t_champ) * MAX_PLAYERS));
	if (data->champs == NULL)
		return (NULL);
	return (data);
}

void	valid_flags(char **argv, int i, t_init *data)
{
	if (ft_valname(argv[i]))
		data->pl_count++;
	else if (!ft_strcmp(argv[i], "-n"))
		data->flag_n++;
	else if (!ft_strcmp(argv[i], "-dump"))
		data->flag_dump++;
	else if (ft_isnumber(argv[i]))
		data->num++;
	else if (!ft_strcmp(argv[i], "-v"))
		data->flag_vis++;
	else if (!ft_strcmp(argv[i], "-a"))
		data->flag_aff++;
	else if (!ft_strcmp(argv[i], "-d"))
		data->flag_d++;
	else
		data->error.help = 1;
}

void	pre_valid(int argc, char **argv, t_init *data)
{
	int i;

	i = 1;
	while (i < argc)
	{
		valid_flags(argv, i, data);
		i++;
	}
	if (data->flag_dump && data->flag_d)
		data->error.help = 1;
	if (data->flag_dump > 1 || data->flag_d > 1 ||
		data->flag_aff > 1 || data->flag_vis > 1)
		data->error.help = 1;
	if (data->num != (data->flag_n + data->flag_dump + data->flag_d))
		data->error.help = 1;
}
