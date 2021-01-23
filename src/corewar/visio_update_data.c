/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visio_update_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:15:15 by dteemo            #+#    #+#             */
/*   Updated: 2021/01/21 17:15:16 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_corewar/corewar.h"

void	put_cell(int row, int col, t_cell cell, WINDOW *win1)
{
	char	*c;

	wcolor_set(win1, 1, NULL);
	c = ft_strnew(3);
	wmove(win1, row, col * 3 + 2);
	if (cell.player != 0)
		wcolor_set(win1, cell.player * 2, NULL);
	else
		wcolor_set(win1, 1, NULL);
	if (cell.car != 0 || cell.if_live != 0)
		wcolor_set(win1, cell.player * 2 + 1, NULL);
	c[0] = hex_char(cell.c / 16);
	c[1] = hex_char(cell.c % 16);
	if (cell.if_st == 1 || cell.if_live == 1)
		wattron(win1, A_BOLD);
	wprintw(win1, c);
	if (cell.if_st == 1 || cell.if_live == 1)
		wattroff(win1, A_BOLD);
	if (cell.car != 0 || cell.if_live != 0)
		wcolor_set(win1, 1, NULL);
}

int		cmp_data(t_vdata *data, int index)
{
	if (data->buf[index].c != data->old_buf[index].c)
		return (0);
	if (data->buf[index].car != data->old_buf[index].car)
		return (0);
	if (data->buf[index].player != data->old_buf[index].player)
		return (0);
	if (data->buf[index].if_st != data->old_buf[index].if_st)
		return (0);
	if (data->buf[index].if_live != data->old_buf[index].if_live)
		return (0);
	return (1);
}

void	update_old(t_vdata *data, int i)
{
	data->old_buf[i].c = data->buf[i].c;
	data->old_buf[i].player = data->buf[i].player;
	data->old_buf[i].car = data->buf[i].car;
	data->old_buf[i].if_st = data->buf[i].if_st;
	data->old_buf[i].if_live = data->buf[i].if_live;
}

void	update_data(t_vdata *data, int start_line, WINDOW *win1)
{
	int		i;
	int		j;

	i = 0;
	i += start_line * VISIO_LINE;
	while (i < MEM_SIZE && i < (LINES * (VISIO_LINE - 3) +
	start_line * VISIO_LINE))
	{
		j = 0;
		while (j < VISIO_LINE)
		{
			if (!cmp_data(data, i + j))
			{
				put_cell(i / VISIO_LINE - start_line + 1, j,
				data->buf[i + j], win1);
				update_old(data, i + j);
			}
			j++;
		}
		i += VISIO_LINE;
	}
	wrefresh(win1);
}
