/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:19:43 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 17:55:00 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_LIFE 5
# define EAT_T 1
# define REST_T 1
# define THINK_T 1
# define TIMEOUT 60
# define WIN_MESSAGE "Now, it's time... To DAAAAAAAANCE!!!"
# define NB_PHILO 7
# define RIGHT(X) (X == NB_PHILO - 1) ? 0 : X + 1
# define LEFT(X) (X == 0) ? NB_PHILO - 1 : X - 1
# define LOSE_PER_TURN (REST_T + EAT_T)

# define PHILO "Philo %d: his state: %s, his life %s; stick_left %s; stick_right %s; hungry_lvl %s\n"

# define DEAD "\x1B[3%dmPhilo %d: !!starving to death!!\x1B[0m\n"
# define RESTB "\x1B[3%dmPhilo %d: start resting. Life %d\x1B[0m\n"
# define RESTE "\x1B[3%dmPhilo %d: stop resting. Life %d\x1B[0m\n"
# define THINKB "\x1B[3%dmPhilo %d: start thinking. Life %d\x1B[0m\n"
# define THINKE "\x1B[3%dmPhilo %d: stop thinking. Life %d\x1B[0m\n"
# define EATB "\x1B[3%dmPhilo %d: start eating. Life %d\x1B[0m\n"
# define EATE "\x1B[3%dmPhilo %d: stop eating. Life %d\x1B[0m\n"
# define DROPL "\x1B[3%dmPhilo %d: drop left stick\x1B[0m\n"
# define DROPR "\x1B[3%dmPhilo %d: drop right stick\x1B[0m\n"
# define TAKEL "\x1B[3%dmPhilo %d: take left stick\x1B[0m\n"
# define TAKER "\x1B[3%dmPhilo %d: take right stick\x1B[0m\n"

# include "libft.h"
# include <pthread.h>

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
void	    	drop_stick(int stick, t_philosophers *philo);
void	    	take_stick(int stick, t_philosophers *philo);
void	    	drop_sticks(t_philosophers *philo);
void	    	take_sticks(t_philosophers *philo);
int				init_sticks(void);
int				init_philo(void);
int				check_sticks(int philo);
#endif
