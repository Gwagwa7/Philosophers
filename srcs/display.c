/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 09:41:12 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/01 10:58:49 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void		display_info_norme(WINDOW **info, int i, int offset)
{
	int		idlen;
	char	*path;

	path = get_state_info(PHI[i].state);
	idlen = ft_strlen(ft_itoa(i + 1));
	mvwprintw(*info, offset + i, 12, "ID [%d] COLOR [", i + 1);
	wattrset(*info, COLOR_PAIR(i + 8));
	mvwprintw(*info, offset + i, 25 + idlen, "   ");
	wattrset(*info, COLOR_PAIR(0));
	mvwprintw(*info, offset + i, 28 + idlen, "]");
	mvwprintw(*info, offset + i + 1, 12, "Status: %s", path);
	mvwprintw(*info, offset + i + 2, 12, "Life: ");
}

void			display_info(WINDOW **info)
{
	int		max[2];
	int		offset;
	int		i;

	i = 0;
	offset = 3;
	getmaxyx(*info, max[0], max[1]);
	wclear(*info);
	wborder(*info, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(*info, 1, (max[0] / 2) - 5, "%s", "PHILOSOPHE");
	while (i < NB_PHILO)
	{
		display_info_norme(info, i, offset);
		wattrset(*info, COLOR_PAIR(2));
		mvwprintw(*info, offset + i + 2, 21, "%d/%d", PHI[i].life, MAX_LIFE);
		wattrset(*info, COLOR_PAIR(0));
		if (i + 1 < NB_PHILO)
			mvwprintw(*info, offset + i + 4, max[1] / 2 - 6, "************");
		i++;
		offset += 5;
	}
	wrefresh(*info);
}

static void		display_philo_norme(WINDOW *philo[], int i, int offset)
{
	wclear(*(philo + i));
	wattrset(*(philo + i), COLOR_PAIR(i + offset));
	wborder(*(philo + i), 0, 0, 0, 0, 0, 0, 0, 0);
	wattrset(*(philo + i), COLOR_PAIR(0));
}

void			display_philo(WINDOW *philo[], int i)
{
	int		max[2];
	int		offset;
	char	*path;

	offset = 7;
	getmaxyx(*(philo), max[0], max[1]);
	if (NB_PHILO > 1)
	{
		wborder(*(philo), 0, 0, 0, 0, 0, 0, 0, 0);
		mvwprintw(*(philo), 7, 7, "f*cking\n\twormhole");
		wrefresh(*(philo));
		while (++i < NB_PHILO + 1)
		{
			path = get_state_face(PHI[i - 1].state);
			((i + offset) > 14) ? offset -= 7 : offset;
			display_philo_norme(philo, i, offset);
			draw_face(*(philo + i), max[1], max[0], path);
			draw_stick(*(philo + i), max[1], max[0], i - 1);
			wrefresh(*(philo + i));
		}
		wborder(*(philo + (NB_PHILO + 1)), 0, 0, 0, 0, 0, 0, 0, 0);
		mvwprintw(*(philo + (NB_PHILO + 1)), 7, 7, "f*cking\n\twormhole");
		wrefresh(*(philo + (NB_PHILO + 1)));
	}
	usleep(750000);
}
