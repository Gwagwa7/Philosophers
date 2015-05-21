#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_LIFE 5
# define EAT_T 1
# define REST_T 2
# define THINK_T 3
# define TIMEOUT 100
# define WIN_MESSAGE "Now, it's time... To DAAAAAAAANCE!!!"
# define NB_PHILO 3


# define PHILO "\x1B[3%dmPhilo %d: his life %d; stick_left %d; stick_right %d\x1B[0m\n"
# define DEAD "\x1B[3%dmPhilo %d: !!starving to death!!\x1B[0m\n"
# define RESTB "\x1B[3%dmPhilo %d: start resting. Life %d\x1B[0m\n"
# define RESTE "\x1B[3%dmPhilo %d: stop resting. Life %d\x1B[0m\n"
# define THINKB "\x1B[3%dmPhilo %d: start thinking. Life %d\x1B[0m\n"
# define THINKE "\x1B[3%dmPhilo %d: stop thinking. Life %d\x1B[0m\n"
# define EATB "\x1B[3%dmPhilo %d: start eating. Life %d\x1B[0m\n"
# define EATE "\x1B[3%dmPhilo %d: stop eating. Life %d\x1B[0m\n"
# define DROPL "\x1B[3%dmPhilo %d: drop left stick\x1B[0m\n"
# define DROPR "\x1B[3%dmPhilo %d: drop right stick\x1B[0m\n"

# include "libft.h"
# include <pthread.h>

typedef pthread_mutex_t t_mutex;

typedef enum	e_state
{
	THINK, REST, EAT, WANT_EAT
}		t_state;

typedef enum	e_hungry
{
	HIGH, MID, LOW
}		        t_hungry;

typedef struct	s_philosophers
{
	t_state		state;
	int		    life;
	int			nb;
	t_hungry	hungry_lvl;
    pthread_t   thread;
    int         stick_left;
    int         stick_right;
}		        t_philosophers;

#endif
