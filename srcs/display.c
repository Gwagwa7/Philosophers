/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 09:41:12 by mschmit           #+#    #+#             */
/*   Updated: 2015/05/28 15:05:52 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../includes/philosophers.h"
#include "../includes/libft.h"

/* 
  Dessiner la table
  placer les portrait de philo tout au tour
  afficher les stick a cote si aucun des philo n'en tiens
*/

static void finish(int sig)
{
	clear();
	endwin();
}

int init_display(void)
{

	initscr();
	noecho();
	keypad(stdscr, TRUE);
	nonl();
	curs_set(FALSE);
	cbreak();
	echo();
	if (has_colors())
	{
		start_color();
		init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_WHITE,   COLOR_BLACK);
        init_pair(8, COLOR_BLACK,   COLOR_RED);
        init_pair(9, COLOR_BLACK,   COLOR_GREEN);
        init_pair(10, COLOR_BLACK,  COLOR_YELLOW);
        init_pair(11, COLOR_BLACK,  COLOR_BLUE);
        init_pair(12, COLOR_BLACK,  COLOR_CYAN);
        init_pair(13, COLOR_BLACK,  COLOR_MAGENTA);
        init_pair(14, COLOR_BLACK,  COLOR_WHITE);
	}
	return (0);
}

void	display_title()
{
	int		maxX;
	int		maxY;
	int		fd;
	char 	*ret;
	int 	i;

	i = -1;
	fd = open("../imgs/title.txt", O_RDONLY);
	getmaxyx(stdscr, maxX, maxY);
	wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
	attrset(COLOR_PAIR(1));
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			mvprintw((maxX / 2) + ++i, (maxY / 2) - 45, "%s", ret);
	wrefresh(stdscr);
	close(fd);
	sleep(2);
	wclear(stdscr);
	wrefresh(stdscr);
}	

void init_info(WINDOW **info)
{
	int		maxX;
	int		maxY;
	
	getmaxyx(stdscr, maxX, maxY);
	*info = newwin(maxX, 40, 0, 0);
	
}

void initndisplay_graph(WINDOW **graph)
{
	int		maxX;
	int		maxY;
	
	getmaxyx(stdscr, maxX, maxY);
	*graph = newwin(maxX, maxY - 41, 0, 41);
	wborder(*graph, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(*graph);
	
}

char *get_state_info(int state)
{
	if (state == 0)
		return ("THINK");
	else if (state == 1)
		return ("REST");
	else if (state == 2)
		return ("EAT");
	else if (state == 3)
		return ("WANT EAT");
	else
		return ("ERROR");

}

char *get_state_face(int state)
{
	if (state == 0)
		return ("../imgs/facethink.txt");
	else if (state == 1)
		return ("../imgs/facerest.txt");
	else if (state == 2)
		return ("../imgs/faceeat.txt");
	else if (state == 3)
		return ("../imgs/facestarve.txt");
	else
		return ("ERROR");

}

void draw_table(WINDOW *win)
{
	int maxX;
	int maxY;
	int x;
	int y;

	x = 0;
	y = 0;
	getmaxyx(win, maxY, maxX);
	while (y < (maxY - (maxY / 3)))
	{
		while (x < (maxX - (maxX / 3)))
		{
			x++;
			mvwaddch(win, y + maxY/5, x + maxX/5, '.');
		}
		x = 0;
		y++;
	}
	wrefresh(win);
}

void display_info(WINDOW **info)
{
	int		maxX;
	int		maxY;
	int		i;
	int 	idlen;
	int		offset;

	
	i = 0;
	offset = 3;
	getmaxyx(*info, maxX, maxY);
	wborder(*info, 0, 0, 0, 0, 0, 0, 0, 0);
	mvwprintw(*info, 1, (maxY / 2) - 5, "%s", "PHILOSOPHE");
	while (i < NB_PHILO)
	{
		idlen = ft_strlen(ft_itoa(i + 1));
		mvwprintw(*info, offset + i, 12, "ID [%d] COLOR [", i + 1);
		wattrset(*info, COLOR_PAIR(i + 8));
		mvwprintw(*info, offset + i, 25 + idlen, "   ");
		wattrset(*info, COLOR_PAIR(0));
		mvwprintw(*info, offset + i, 28 + idlen, "]");
		mvwprintw(*info, offset + i + 1, 12, "Status: %s", get_state_info(i));
		mvwprintw(*info, offset + i + 2, 12, "Life: ");
		wattrset(*info, COLOR_PAIR(2));
		mvwprintw(*info, offset + i + 2, 21, "%d/%d", 22, MAX_LIFE );
		wattrset(*info, COLOR_PAIR(0));
		if( i + 1 < NB_PHILO)
			mvwprintw(*info, offset + i + 4, maxY / 2 - 6, "************");
		i++;
		offset += 5;
	}
	wrefresh(*info);
}

void init_philo_win(WINDOW *philo[], WINDOW *graph)
{
	int i;
	int maxX;
	int maxY;
	int y;
	int x;

	y = 10;
	x = 50;
	getmaxyx(graph, maxY, maxX);
	i = -1;
	if(NB_PHILO > 1)
	{
		while(++i < NB_PHILO)
		{
			*(philo + i) = newwin(15, 27, y, x);
			
			if (y > maxY + 1000)
			{
				x -= 28;
			}
			else if (x > maxX)
			{
				y+= 16;
			}
			else
			{
				x += 28;
			}
			
		}
	}	
}

void draw_stick(WINDOW *philo, int maxY, int maxX)
{
	char 	*ret;
	int		fd;
	int 	fd2;
	int 	i;
	int 	Lstick;
	int 	Rstick;

	i = 6;
	Lstick = 1;
	Rstick = 1;
	fd = open("../imgs/Lstick.txt", O_RDONLY);
	fd2 = open("../imgs/Rstick.txt", O_RDONLY);
	wattrset(philo, COLOR_PAIR(3));
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			if(Lstick == 1)
				mvwprintw(philo, ++i, maxY - 6, "%s", ret);
	i = 6;
	if (fd2 != -1)
		while (get_next_line(fd2, &ret) != 0)
			if(Rstick == 1)
				mvwprintw(philo, ++i, 1, "%s", ret);
	close(fd);
	close(fd2);

}

void draw_face(WINDOW *philo, int maxY, int maxX, char *path)
{
	char 	*ret;
	int		fd;
	int 	i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			mvwprintw(philo, ++i, (maxY / 2) - (ft_strlen(ret) / 2), "%s", ret);
	close(fd);
}


void display_philo(WINDOW *philo[])
{
	int i;
	int		maxX;
	int		maxY;
	i = -1;
	getmaxyx(*(philo), maxX, maxY);
	if(NB_PHILO > 1)
	{
		while(++i < NB_PHILO)
		{
			wattrset(*(philo + i), COLOR_PAIR(i + 8));
			wborder(*(philo + i), 0, 0, 0, 0, 0, 0, 0, 0);
			wattrset(*(philo + i), COLOR_PAIR(0));
			draw_face(*(philo + i), maxY, maxX, get_state_face(i));
			draw_stick(*(philo + i), maxY, maxX);
			wrefresh(*(philo + i));

		}
	}

	sleep(1);
}

int main(void)
{
	int		c;
	int		num;
	WINDOW *info;
	WINDOW *graph;
	WINDOW *philo[NB_PHILO];

	init_display();
	display_title();

	init_info(&info);
	initndisplay_graph(&graph);
	init_philo_win(philo, graph);

	draw_table(graph);
	display_info(&info);
	display_philo(philo);
	
	sleep(10);
	finish(0);
	return (1);
}