#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <philosophers.h>

t_philosophers  philosophers[NB_PHILO];
pthread_mutex_t    sticks[NB_PHILO];

void    drop_stick(int n)
{
    pthread_mutex_unlock(&(sticks[n]));
}

int     take_stick(int n)
{
    return (1);
}

void    update_hungry(t_philosophers *philo)
{
    int life_percent;

    life_percent = philo->life / MAX_LIFE * 100;
    if (life_percent <= 33)
        philo->hungry_lvl = HIGH;
    else if (life_percent <= 66)
        philo->hungry_lvl = MID;
    else
        philo->hungry_lvl = LOW;
}

void    rest(int n1)
{
    int n2;
    time_t  t1;
    time_t  t2;

    printf("Philosopher %d start resting. Life %d\n", n1, philosophers[n1].life);
    n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
    if (philosophers[n1].stick_left)
    {
        drop_stick(n1);
        philosophers[n1].stick_left = 0;
    }
    if (philosophers[n1].stick_right)
    {
        drop_stick(n2);
        philosophers[n1].stick_right = 0;
    }
    philosophers[n1].state = REST;
    time(&t1);
    time(&t2);
    while (t2 - t1 < REST_T)
    {
        time(&t2);
        usleep(100000);
    }
    philosophers[n1].life -= REST_T * 1000;
    update_hungry(&(philosophers[n1]));
    printf("Philosopher %d stop resting. Life %d\n", n1, philosophers[n1].life);
}

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
    return (1);
}

void    *rootine(void *param)
{
    while (no_philo_dead())
    {

    }
}

int    init_philo(void)
{
    int i;

    if (MAX_LIFE * 1000 < INT_MAX)
    {
        ft_putendl("Too much life !");
        return (0);
    }
    i = 0;
    while (i < NB_PHILO)
    {
        philosophers[i].life = MAX_LIFE * 1000;
        philosophers[i].hungry_lvl = LOW;
        philosophers[i].state = REST;
        philosophers[i].stick_right = 0;
        philosophers[i].stick_left = 0;
        pthread_create(&(philosophers[i].thread), NULL, rootine, &i);
        i++;
    }
    return (1);
}

int	main(void)
{

	return (0);
}
