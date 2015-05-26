/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 09:41:12 by mschmit           #+#    #+#             */
/*   Updated: 2015/05/26 14:25:00 by mschmit          ###   ########.fr       */
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
	// resize_term(640, 480); << repare ca avant la fin.
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

void init_graph(WINDOW **graph)
{
	int		maxX;
	int		maxY;
	
	getmaxyx(stdscr, maxX, maxY);
	*graph = newwin(maxX, maxY - 41, 0, 41);
	
}

char *get_state(int state)
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

void draw_face(WINDOW **graph, int maxY, int maxX, char *path)
{
	char 	*ret;
	int		fd;
	int 	i;

	i = -1;
	fd = open(path, O_RDONLY);
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			mvwprintw(*graph, (maxX / 2) + ++i, (maxY / 2) - (ft_strlen(ret) / 2), "%s", ret);
	close(fd);
}

// void draw_table(WINDOW **graph)
// {
// 	mvwprintw(*info, offset + i, 12, "ID [");
// }

void display_graph(WINDOW **graph)
{
	int		maxX;
	int		maxY;
	
	getmaxyx(*graph, maxX, maxY);
	wborder(*graph, 0, 0, 0, 0, 0, 0, 0, 0);
	draw_face(graph, maxY, maxX, "../imgs/facerest.txt");
	wrefresh(*graph);
	sleep(1);
	draw_face(graph, maxY, maxX, "../imgs/facesleep.txt");
	wrefresh(*graph);
	sleep(1);
	draw_face(graph, maxY, maxX, "../imgs/facethink.txt");
	wrefresh(*graph);
	sleep(1);
	draw_face(graph, maxY, maxX, "../imgs/facestarve.txt");
	wrefresh(*graph);
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
	while (i < NB_PHILO + 5)
	{
		idlen = ft_strlen(ft_itoa(i + 1));
		mvwprintw(*info, offset + i, 12, "ID [%d] COLOR [", i + 1);
		wattrset(*info, COLOR_PAIR(i + 8));
		mvwprintw(*info, offset + i, 25 + idlen, " ");
		wattrset(*info, COLOR_PAIR(0));
		mvwprintw(*info, offset + i, 26 + idlen, "]");
		mvwprintw(*info, offset + i + 1, 12, "Status: %s", get_state(i));
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

int main(void)
{
	int		c;
	int		num;
	WINDOW *info;
	WINDOW *graph;

	num = 0;
	init_display();
	display_title();
	init_info(&info);
	init_graph(&graph);
	display_info(&info);
	display_graph(&graph);
	sleep(5);
	// while(1)
	// {
	// 	c = getch();
	// 	attrset(COLOR_PAIR(num % 8));
	// 	num++;
	// }
	finish(0);
	return (1);
}