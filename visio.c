#include "corewar.h"

void	start_visio(t_vdata *vdata)
{
	initscr();
	vdata->win1 = newwin(LINES, VISIO_LINE * 3 + 3, 0, 0);
	vdata->win2 = newwin(LINES, COLS - VISIO_LINE * 3 - 3, 0, VISIO_LINE * 3 + 3);
	vdata->run_status = 1;
	refresh();
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

void	end_visio(t_vdata *vdata)
{
	delwin(vdata->win1);
	delwin(vdata->win2);
	free(vdata);
	endwin();
}

void	begin_visio(t_init *data, t_vdata *vdata)
{
	start_visio(vdata);
	create_cells(vdata, data);
	put_data(vdata, 0, vdata->win1);
	put_attrs(data, vdata->win2);
	curs_set(0);
}

void	run_visio(t_vdata *vdata)
{
	int		ch;
	
	if (vdata->run_status == 1)
		while ((ch = getch()) != 'r')
			continue ;
	vdata->run_status = 0;
	wmove(vdata->win2, 2, 2);
	wprintw(vdata->win2, " **RUNNING**");
}

void	update_visio(t_init *data, t_vdata *vdata)
{
	update_cells(vdata, data);
	update_data(vdata, 0, vdata->win1);
	update_attrs(data, vdata->win2);
	usleep(1000000 / VISIO_LIMIT);
}
