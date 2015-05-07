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

void     take_stick(int n)
{
    pthread_mutex_lock(&(sticks[n]));
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

void    eat(int n1)
{
    int n2;
    time_t  t1;
    time_t  t2;

    printf("Philosopher %d start eating. Life %d\n", n1, philosophers[n1].life);
    n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
    philosophers[n1].state = EAT;
    time(&t1);
    time(&t2);
    while (t2 - t1 < EAT_T)
    {
        time(&t2);
        usleep(100000);
    }
    philosophers[n1].life = MAX_LIFE * 1000;
    update_hungry(&(philosophers[n1]));
    printf("Philosopher %d stop eating. Life %d\n", n1, philosophers[n1].life);
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

void    think(int n1)
{
    int n2;
    time_t  t1;
    time_t  t2;

    printf("Philosopher %d start thinking. Life %d\n", n1, philosophers[n1].life);
    n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
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

int     check_sticks(int n1)
{
    int right;
    int left;
    int nb_stick;

    right = (n1 == NB_PHILO) ? 0 : n1 + 1;
    left = (n1 == 0) ? NB_PHILO : n1 - 1;
    nb_stick = 0;
    if (!philosophers[n1].stick_left && !philosophers[left].stick_right)
    {
        take_stick(n1);
        philosophers[n1].stick_left = 1;
        philosophers[left].stick_right = 0;
        nb_stick++;
    }
    else if (philosophers[n1].stick_left)
        nb_stick++;
    if (!philosophers[n1].stick_right && !philosophers[right].stick_left)
    {
        take_stick(right);
        philosophers[n1].stick_right = 1;
        philosophers[right].stick_left = 0;
        nb_stick++;
    }
    else if (philosophers[n1].stick_right)
        nb_stick++;
    return (nb_stick);
}

void    *rootine(void *param)
{
    int *i;
    int ret;

    i = (int *)param;
    while (no_philo_dead())
    {
        rest(*i);
        if ((ret = check_sticks(*i)) == 1)
            think(*i);
        else if (ret == 2)
            eat(*i);
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
