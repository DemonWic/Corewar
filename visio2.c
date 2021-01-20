#include "corewar.h"

void	v_colors()
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

void	v_line(WINDOW *win2, int n)
{
	int		i;

	i = 0;
	while (i++ < n)
		wprintw(win2, " ");
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

void	update_old(t_vdata *data, int i)
{
	data->old_buf[i].c = data->buf[i].c;
	data->old_buf[i].player = data->buf[i].player;
	data->old_buf[i].car = data->buf[i].car;
	data->old_buf[i].if_st = data->buf[i].if_st;
	data->old_buf[i].if_live = data->buf[i].if_live;
}

void	put_plyers(t_init *data, WINDOW *win2)
{
	int		i;

	i = 0;
	while (i < data->pl_count)
	{
		wmove(win2, 12 + i * 3, 3);
		wprintw(win2, "Player ");
		wprintw(win2, ft_itoa(data->champs[i]->num));
		wprintw(win2, " : ");
		wcolor_set(win2, data->champs[i]->num * 2, NULL);
		wprintw(win2, data->champs[i]->name);
		wcolor_set(win2, 1, NULL);
		wmove(win2, 12 + i * 3 + 1, 7);
		wprintw(win2, "Last live : ");
		wprintw(win2, ft_itoa(data->champs[i]->visio_last_live));
		i++;
	}
}

void	put_attrs(t_init *data, WINDOW *win2)
{
		int		i;

	i = 1;
	v_colors();	
	wclear(win2);
	wbkgd(win2, COLOR_PAIR(10));
	wcolor_set(win2, 1, NULL);
	wattron(win2, A_BOLD | A_DIM);
	while (i < LINES - 1)
	{
		wmove(win2, i++, 1);
		v_line(win2, 60);
	}

	wmove (win2, 2, 2);
	wprintw(win2, " **PAUSED**");
	wmove (win2, 4, 2);
	wprintw(win2, " Cycles/second limit : ");
	wprintw(win2, ft_itoa(VISIO_LIMIT));
	wmove (win2, 8, 2);
	wprintw(win2, " Cycle : ");
	wprintw(win2, ft_itoa(data->cycle));
	wmove (win2, 10, 2);
	wprintw(win2, " Processes : ");
	wprintw(win2, ft_itoa(data->cursors_count));
	put_plyers(data, win2);
	wmove (win2, 12 + data->pl_count * 3, 2);
	wprintw(win2, " CYCLE_TO_DIE : ");
	wprintw(win2, ft_itoa(CYCLE_TO_DIE));
	wmove (win2, 14 + data->pl_count * 3, 2);
	wprintw(win2, " CYCLE_DELTA : ");
	wprintw(win2, ft_itoa(CYCLE_DELTA));
	wmove (win2, 16 + data->pl_count * 3, 2);
	wprintw(win2, " NBR_LIVE : ");
	wprintw(win2, ft_itoa(NBR_LIVE));
	wmove (win2, 18 + data->pl_count * 3, 2);
	wprintw(win2, " MAX_CHECKS : ");
	wprintw(win2, ft_itoa(MAX_CHECKS));
	wrefresh(win2);
}

void	update_players(t_init *data, WINDOW *win2)
{
	int		i;

	i = 0;
	while (i < data->pl_count)
	{
		wmove(win2, 12 + i * 3 + 1, 19);
		wprintw(win2, ft_itoa(data->champs[i]->visio_last_live));
		i++;
	}
}

void	update_attrs(t_init *data, WINDOW *win2)
{
	wmove (win2, 8, 2);
	wprintw(win2, " Cycle : ");
	wprintw(win2, ft_itoa(data->cycle));
	wmove (win2, 10, 2);
	wprintw(win2, " Processes : ");
	wprintw(win2, ft_itoa(data->cursors_count));
	update_players(data, win2);
	wmove (win2, 12 + data->pl_count * 3, 2);
	wprintw(win2, " CYCLE_TO_DIE : ");
	wprintw(win2, ft_itoa(data->cycles_to_die));
	wrefresh(win2);
}

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

void	update_data(t_vdata *data, int start_line, WINDOW *win1)
{
	int		i;
	int		j;

	i = 0;
	i += start_line * VISIO_LINE;
	while (i < MEM_SIZE && i < (LINES * (VISIO_LINE - 3) + start_line * VISIO_LINE))
	{
		j = 0;
		while (j < VISIO_LINE)
		{
			if (!cmp_data(data, i + j))
			{
				put_cell(i / VISIO_LINE - start_line + 1, j, data->buf[i + j], win1);
				update_old(data, i + j);
			}
			j++;
		}
		i += VISIO_LINE;
	}
	wrefresh(win1);
}

void	put_data(t_vdata *data, int start_line, WINDOW *win1)
{
	int		i;
	int		j;
	char	*c;
	int		cur_l;

	wclear(win1);
	i = 0;
	c = ft_strnew(3);
	v_colors();
	wbkgd(win1, COLOR_PAIR(10));
	cur_l = 1;
	i += start_line * VISIO_LINE;
	wmove(win1, 1, 1);
	while (i < MEM_SIZE && i < (LINES * (VISIO_LINE - 3) + start_line * VISIO_LINE))
	{
		j = 0;
		wcolor_set(win1, 1, NULL);
		wprintw(win1, " ");
		while (j < VISIO_LINE)
		{
			if (data->buf[i + j].player != 0)
				wcolor_set(win1, data->buf[i + j].player * 2, NULL);
			else
				wcolor_set(win1, 1, NULL);
			if (data->buf[i + j].car != 0 || data->buf[i + j].if_live != 0)
				wcolor_set(win1, data->buf[i + j].player * 2 + 1, NULL);
			c[0] = hex_char(data->buf[i + j].c / 16);
			c[1] = hex_char(data->buf[i + j].c % 16);
			if (data->buf[i + j].if_st == 1 || data->buf[i + j].if_live == 1)
				wattron(win1, A_BOLD);
			wprintw(win1, c);
			if (data->buf[i + j].if_st == 1 || data->buf[i + j].if_live == 1)
				wattroff(win1, A_BOLD);
			if (data->buf[i + j].car != 0 || data->buf[i + j].if_live != 0)
				wcolor_set(win1, 1, NULL);
			wprintw(win1, " ");
			j++;
		}
		i += VISIO_LINE;
		wmove(win1, ++cur_l, 1);
	}
	free(c);
	init_old_buf(data);
	wrefresh(win1);
}
