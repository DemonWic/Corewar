/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:22:38 by dteemo            #+#    #+#             */
/*   Updated: 2021/01/23 14:22:39 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	start_visio(t_vdata *vdata)
{
	int		i;

	initscr();
	i = VISIO_LINE;
	vdata->win1 = newwin(LINES, i * 3 + 3, 0, 0);
	vdata->win2 = newwin(LINES, COLS - i * 3 - 3, 0, i * 3 + 3);
	vdata->run_status = 1;
	refresh();
	v_colors();
}

void	end_visio(t_vdata *vdata, t_init *data)
{
	kill_visio(vdata, data);
	delwin(vdata->win1);
	delwin(vdata->win2);
	free(vdata);
	endwin();
}

t_vdata	*begin_visio(t_init *data)
{
	t_vdata	*vdata;

	vdata = (t_vdata*)malloc(sizeof(t_vdata));
	start_visio(vdata);
	create_cells(vdata, data);
	put_data(vdata, 0, vdata->win1);
	put_attrs(data, vdata->win2);
	curs_set(0);
	return (vdata);
}

void	run_visio(t_vdata *vdata)
{
	int		ch;

	if (vdata->run_status == 1)
		while ((ch = getch()) != ' ')
			continue ;
	vdata->run_status = 0;
	wmove(vdata->win2, 2, 2);
	wprintw(vdata->win2, " **RUNNING**");
}

void	kill_visio(t_vdata *vdata, t_init *data)
{
	int		ch;
	int		k;

	k = data->live_player - 1;
	wmove(vdata->win2, 32, 2);
	wprintw(vdata->win2, " CHAMPION WIN : ");
	wcolor_set(vdata->win2, data->champs[k]->num * 2, NULL);
	wprintw(vdata->win2, data->champs[k]->name);
	wcolor_set(vdata->win2, 1, NULL);
	wmove(vdata->win2, 34, 2);
	wprintw(vdata->win2, " PRESS \'q\' TO QUIT!!!");
	wrefresh(vdata->win2);
	while ((ch = getch()) != 'q')
		continue ;
}
