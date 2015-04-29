#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_LIFE 10
# define EAT_T 10
# define REST_T 10
# define THINK_T 10
# define TIMEOUT 100
# define WIN_MESSAGE "Now, it's time... To DAAAAAAAANCE!!!"
# define NB_PHILO 7

# include <pthread.h>

typedef enum	e_state
{
	THINK, REST, EAT
}		t_state;

typedef enum	e_hungry
{
	VERY, MID, LOW
}		t_hungry;

typedef struct	s_philosophers
{
	t_state		state;
	int		    life;
	t_hungry	hungry_lvl;
    pthread_t   thread;
}		t_philosophers;

#endif
