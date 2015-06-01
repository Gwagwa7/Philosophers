/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 10:47:28 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/01 11:02:39 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int				init_display(void)
{
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		init_pair(5, COLOR_CYAN, COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
		init_pair(8, COLOR_BLACK, COLOR_RED);
		init_pair(9, COLOR_BLACK, COLOR_GREEN);
		init_pair(10, COLOR_BLACK, COLOR_YELLOW);
		init_pair(11, COLOR_BLACK, COLOR_BLUE);
		init_pair(12, COLOR_BLACK, COLOR_CYAN);
		init_pair(13, COLOR_BLACK, COLOR_MAGENTA);
		init_pair(14, COLOR_BLACK, COLOR_WHITE);
	}
	display_title();
	return (0);
}

void			init_info(WINDOW **info)
{
	int		maxx;
	int		maxy;

	getmaxyx(stdscr, maxx, maxy);
	*info = newwin(maxx, 40, 0, 0);
}

void			initndisplay_graph(WINDOW **graph, WINDOW **info)
{
	int		maxx;
	int		maxy;

	getmaxyx(stdscr, maxx, maxy);
	*graph = newwin(maxx, maxy - 41, 0, 41);
	wborder(*graph, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(*graph);
	init_info(info);
}

void			init_philo_win(WINDOW *philo[], WINDOW *graph)
{
	int		i;
	int		axis[2];
	int		maxaxis[2];

	i = 0;
	getmaxyx(graph, maxaxis[0], maxaxis[1]);
	axis[0] = 1;
	axis[1] = 43;
	if (NB_PHILO > 1)
		while (i < NB_PHILO + 2)
		{
			*(philo + i) = newwin(15, 27, axis[0], axis[1]);
			axis[1] += 27;
			if (axis[1] > maxaxis[1])
			{
				axis[1] = 43;
				axis[0] += 15;
			}
			i++;
		}
}
