#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_LIFE 25
# define EAT_T 1
# define REST_T 2
# define THINK_T 3
# define TIMEOUT 100
# define WIN_MESSAGE "Now, it's time... To DAAAAAAAANCE!!!"
# define NB_PHILO 7


# define PHILO "Philo %d: his state: %s, his life %s; stick_left %s; stick_right %s\n"

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

typedef pthread_mutex_t t_mutex;

typedef enum	e_state
{
	THINK, REST, EAT, WANT_EAT
}		t_state;

typedef enum	e_hungry
{
	HIGH = 0, MID = 1, LOW = 2
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
