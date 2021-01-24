/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visio_cells.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:10:29 by dteemo            #+#    #+#             */
/*   Updated: 2021/01/21 17:10:31 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	create_cells(t_vdata *vdata, t_init *data)
{
	int			i;
	t_cursor	*c;

	i = 0;
	while (i < MEM_SIZE)
	{
		vdata->buf[i].c = data->arena[i];
		vdata->buf[i].player = data->col_arena[i];
		vdata->buf[i].car = 0;
		vdata->buf[i].if_st = 0;
		vdata->buf[i].if_live = 0;
		i++;
	}
	c = data->cursors;
	while (c)
	{
		vdata->buf[c->pc].car = 1;
		c = c->next;
	}
}

void	update_cells2(t_vdata *vdata, t_init *data, int i)
{
	if (vdata->buf[i].c != data->arena[i])
		vdata->buf[i].c = data->arena[i];
	if (vdata->buf[i].player != data->col_arena[i])
		vdata->buf[i].player = data->col_arena[i];
	if (data->st_arena[i] != 0)
	{
		vdata->buf[i].if_st = 1;
		data->st_arena[i]--;
	}
	else
		vdata->buf[i].if_st = 0;
	if (data->l_arena[i] != 0)
	{
		vdata->buf[i].if_live = 1;
		data->l_arena[i]--;
	}
	else
		vdata->buf[i].if_live = 0;
	vdata->buf[i].car = 0;
}

void	update_cells(t_vdata *vdata, t_init *data)
{
	int			i;
	t_cursor	*c;

	i = 0;
	while (i < MEM_SIZE)
	{
		update_cells2(vdata, data, i);
		i++;
	}
	c = data->cursors;
	while (c)
	{
		vdata->buf[c->pc].car = 1;
		c = c->next;
	}
}
