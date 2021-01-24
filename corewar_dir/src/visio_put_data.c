/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visio_put_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:14:59 by dteemo            #+#    #+#             */
/*   Updated: 2021/01/21 17:15:01 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	v_colors(void)
{
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(8, COLOR_RED, COLOR_BLACK);
	init_pair(9, COLOR_WHITE, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void	init_old_buf(t_vdata *data)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		data->old_buf[i].c = data->buf[i].c;
		data->old_buf[i].player = data->buf[i].player;
		data->old_buf[i].car = data->buf[i].car;
		data->old_buf[i].if_st = data->buf[i].if_st;
		data->old_buf[i].if_live = data->buf[i].if_live;
		i++;
	}
}

void	put_one(t_vdata *data, WINDOW *win1, int a, char *c)
{
	if (data->buf[a].player != 0)
		wcolor_set(win1, data->buf[a].player * 2, NULL);
	else
		wcolor_set(win1, 1, NULL);
	if (data->buf[a].car != 0 || data->buf[a].if_live != 0)
		wcolor_set(win1, data->buf[a].player * 2 + 1, NULL);
	c[0] = hex_char(data->buf[a].c / 16);
	c[1] = hex_char(data->buf[a].c % 16);
	if (data->buf[a].if_st == 1 || data->buf[a].if_live == 1)
		wattron(win1, A_BOLD);
	wprintw(win1, c);
	if (data->buf[a].if_st == 1 || data->buf[a].if_live == 1)
		wattroff(win1, A_BOLD);
	if (data->buf[a].car != 0 || data->buf[a].if_live != 0)
		wcolor_set(win1, 1, NULL);
	wprintw(win1, " ");
}

int		put_data2(WINDOW *win1)
{
	wclear(win1);
	v_colors();
	wbkgd(win1, COLOR_PAIR(10));
	wmove(win1, 1, 1);
	return (1);
}

void	put_data(t_vdata *data, int start_line, WINDOW *win1)
{
	int		i;
	int		j;
	char	*c;
	int		cur_l;

	i = start_line * VISIO_LINE;
	c = ft_strnew(3);
	cur_l = put_data2(win1);
	while (i < MEM_SIZE && i < (LINES * (VISIO_LINE - 3) +
	start_line * VISIO_LINE))
	{
		j = 0;
		wcolor_set(win1, 1, NULL);
		wprintw(win1, " ");
		while (j < VISIO_LINE)
		{
			put_one(data, win1, i + j, c);
			j++;
		}
		i += VISIO_LINE;
		wmove(win1, ++cur_l, 1);
	}
	free(c);
	init_old_buf(data);
	wrefresh(win1);
}
