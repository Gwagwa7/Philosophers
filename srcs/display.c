/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 09:41:12 by mschmit           #+#    #+#             */
/*   Updated: 2015/05/26 16:20:53 by mschmit          ###   ########.fr       */
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
   Trouver comment caster le tab de win_philo
   Passer les x et Y des faces et des sticks dans win_philo
   ajouter la fonction pour que les win_philo soient en rond
   et ok !!
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
/* changer les coordonnees, integrer dns win_philo */
void draw_face(WINDOW **graph, int maxY, int maxX, char *path)
{
	char 	*ret;
	int		fd;
	int 	i;

	i = -1;
	fd = open(path, O_RDONLY);
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
		{
			mvwprintw(*graph, (maxX / 2) + ++i, (maxY / 2) - (ft_strlen(ret) / 2), "%s", ret);
		}
	close(fd);
}
/* changer les coordonnees, integrer dns win_philo */
void draw_stick(WINDOW **graph, int maxY, int maxX)
{
	char 	*ret;
	int		fd;
	int 	fd2;
	int 	i;
	int 	Lstick;
	int 	Rstick;

	i = -1;
	Lstick = 1;
	Rstick = 1;
	fd = open("../imgs/Lstick.txt", O_RDONLY);
	fd2 = open("../imgs/Rstick.txt", O_RDONLY);
	if (fd != -1)
		while (get_next_line(fd, &ret) != 0)
			if(Lstick == 1)
				mvwprintw(*graph, (maxX / 2) + ++i, (maxY / 2) - (ft_strlen(ret) / 2)+ 20, "%s", ret);
	i = -1;
	if (fd2 != -1)
		while (get_next_line(fd2, &ret) != 0)
			if(Rstick == 1)
				mvwprintw(*graph, (maxX / 2) + ++i, (maxY / 2) - (ft_strlen(ret) / 2), "%s", ret);
	close(fd);
	close(fd2);

}

void display_graph(WINDOW **graph)
{
	int		maxX;
	int		maxY;
	int 	i;
	int 	y;
	int 	facex;
	int 	facey;

	i = 0;
	y = 42;
	facex = 20;
	facey = 13;
	getmaxyx(*graph, maxX, maxY);
	wborder(*graph, 0, 0, 0, 0, 0, 0, 0, 0);
	while (i < NB_PHILO)
	{
		draw_face(graph, y, maxX, get_state_face(i));
		draw_stick(graph, y, maxX);
		y+= 45;
		i++;
	}
	wrefresh(*graph);
	sleep(1);
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
		mvwprintw(*info, offset + i, 25 + idlen, " ");
		wattrset(*info, COLOR_PAIR(0));
		mvwprintw(*info, offset + i, 26 + idlen, "]");
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

/* corriger le cast, renvoyer les bonne coordonnees pour les mettre en cercle */
void init_philo_win(WINDOW **philo[])
{
	int i;
	int maxX;
	int maxY;
	int offset;

	i = -1;
	offset = 0;
	getmaxyx(stdscr, maxX, maxY);
	while(++i < NB_PHILO)
	{
		*philo[i] = newwin(14, 20, 10, 10 + offset);
		ft_putendl("tab");
		ft_putnbr(i);
		offset += 20;
	}
	
	
}

int main(void)
{
	int		c;
	int		num;
	WINDOW *info;
	WINDOW *graph;
	WINDOW *philo[NB_PHILO];

	num = 0;
	init_display();
	display_title();
	init_info(&info);
	init_graph(&graph);

	init_philo_win((WINDOW ***)philo);

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