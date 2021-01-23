/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visio_put_attrs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:14:52 by dteemo            #+#    #+#             */
/*   Updated: 2021/01/21 17:14:54 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	v_line(WINDOW *win2, int n)
{
	int		i;

	i = 0;
	while (i++ < n)
		wprintw(win2, " ");
}

void	put_attrs2(t_init *data, WINDOW *win2)
{
	wprintw(win2, " Cycle : ");
	wprintw(win2, ft_itoa(data->cycle));
	wmove(win2, 10, 2);
	wprintw(win2, " Processes : ");
	wprintw(win2, ft_itoa(data->cursors_count));
	put_plyers(data, win2);
	wmove(win2, 12 + data->pl_count * 3, 2);
	wprintw(win2, " CYCLE_TO_DIE : ");
	wprintw(win2, ft_itoa(CYCLE_TO_DIE));
	wmove(win2, 14 + data->pl_count * 3, 2);
	wprintw(win2, " CYCLE_DELTA : ");
	wprintw(win2, ft_itoa(CYCLE_DELTA));
	wmove(win2, 16 + data->pl_count * 3, 2);
	wprintw(win2, " NBR_LIVE : ");
	wprintw(win2, ft_itoa(NBR_LIVE));
	wmove(win2, 18 + data->pl_count * 3, 2);
	wprintw(win2, " MAX_CHECKS : ");
	wprintw(win2, ft_itoa(MAX_CHECKS));
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
	wmove(win2, 2, 2);
	wprintw(win2, " **PAUSED**");
	wmove(win2, 4, 2);
	wprintw(win2, " Cycles/second limit : ");
	wprintw(win2, ft_itoa(VISIO_LIMIT));
	wmove(win2, 8, 2);
	put_attrs2(data, win2);
	wrefresh(win2);
}
