/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:19:43 by mcassagn          #+#    #+#             */
/*   Updated: 2015/06/01 11:02:28 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_LIFE 10
# define EAT_T 1
# define REST_T 1
# define THINK_T 1
# define TIMEOUT 60
# define WIN_MESSAGE "Now, it's time... To DAAAAAAAANCE!!!"
# define NB_PHILO 7
# define RIGHT(X) (X == NB_PHILO - 1) ? 0 : X + 1
# define LEFT(X) (X == 0) ? NB_PHILO - 1 : X - 1
# define LOSE_PER_TURN (REST_T + EAT_T)
# define PHI g_philosophers
# include "libft.h"
# include <pthread.h>
# include <ncurses.h>
# include <ncurses.h>
# include <curses.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef pthread_mutex_t	t_mutex;

typedef enum	e_state
{
	THINK, REST, EAT, WANT_EAT
}				t_state;

typedef enum	e_hungry
{
	LOW = 0, MEDIUM, HIGH, CRITICAL
}				t_hungry;

typedef struct	s_philosophers
{
	t_state		state;
	int			life;
	int			nb;
	t_hungry	hungry_lvl;
	pthread_t	thread;
	int			stick_left;
	int			stick_right;
	int			need_left_stick;
	int			need_right_stick;
}				t_philosophers;

t_philosophers	g_philosophers[NB_PHILO];
t_mutex			g_sticks[NB_PHILO];

void			eat(t_philosophers *philo);
void			think(t_philosophers *philo);
void			rest(t_philosophers *philo);
void			update_hungry(t_philosophers *philo);
int				no_philo_dead(void);
void			init_stick(void);
void			*main_rootine(void *param);
void			*philo_rootine(void *param);
void			drop_stick(int stick, t_philosophers *philo);
void			take_stick(int stick, t_philosophers *philo);
void			drop_sticks(t_philosophers *philo);
void			take_sticks(t_philosophers *philo);
int				init_sticks(void);
int				init_philo(void);
int				check_sticks(int philo);
void			set_sticks(t_philosophers *philo, int i);

int				init_display(void);
void			init_info(WINDOW **info);
void			initndisplay_graph(WINDOW **graph, WINDOW **info);
void			init_philo_win(WINDOW *philo[], WINDOW *graph);
void			display_info(WINDOW **info);
void			finish(int sig);
void			display_philo(WINDOW *philo[], int i);
void			display_title(void);
char			*get_state_info(int state);
char			*get_state_face(int state);
void			draw_stick(WINDOW *philo, int maxy, int maxx, int index);
void			draw_face(WINDOW *philo, int maxy, int maxx, char *path);
#endif
