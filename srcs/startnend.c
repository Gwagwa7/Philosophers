/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startnend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 10:54:22 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/01 12:57:59 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include <stdlib.h>

void			finish(WINDOW *philo[])
{
	int	i;

	i = 0;
	clear();
	while (i < NB_PHILO + 2)
	{
		delwin(philo[i]);
		i++;
	}
	endwin();
}

void			display_title(void)
{
	int		maxx;
	int		maxy;
	int		fd;
	char	*ret;
	int		i;

	i = -1;
	fd = open("./imgs/title.txt", O_RDONLY);
	getmaxyx(stdscr, maxx, maxy);
	wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
	attrset(COLOR_PAIR(1));
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			mvprintw((maxx / 2) + ++i, (maxy / 2) - 45, "%s", ret);
	wrefresh(stdscr);
	close(fd);
	sleep(2);
	wclear(stdscr);
	wrefresh(stdscr);
}
