#include <philosophers.h>

t_philosophers  philosophers[NB_PHILO];

int     no_philo_dead(void)
{
    int    i;

    i = 0;
    while (i < NB_PHILO)
    {
        if (philosophers[i].life < 1)
            return (0);
        i++;
    }
    return (0);
}

void    init_philo(void)
{
    int i;

    i = 0;
    while (i < NB_PHILO)
    {
        philosophers[i].life = MAX_LIFE;
        philosophers[i].hungry_lvl = LOW;
        pthread_create(&(philosophers[i].thread), )
    }
}

void    *rootine(void *param)
{
    while (no_philo_dead())
    {
    }
}

int	main(void)
{
	return (0);
}
