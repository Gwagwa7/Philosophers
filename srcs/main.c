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
		usleep(100);
	}
	philosophers[n1].life = MAX_LIFE;
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
		usleep(100);
	}
	philosophers[n1].life -= REST_T;
	update_hungry(&(philosophers[n1]));
	printf("Philosopher %d stop resting. Life %d\n", n1, philosophers[n1].life);
}

int		neigbhor_is_hungry(int n)
{
	if (philosophers[n].hungry_lvl == HIGH)
		return (1);
	return (0);
}

void    think(int n1)
{
	int n2;
	time_t  t1;
	time_t  t2;

	printf("Philosopher %d start thinking. Life %d\n", n1, philosophers[n1].life);
	n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
	time(&t1);
	time(&t2);
	while (t2 - t1 < REST_T)
	{
		if (neigbhor_is_hungry(n1) && philosophers[n1].stick_left)
		{
			drop_stick(n1);
			philosophers[n1].stick_left = 0;
		}
		if (neigbhor_is_hungry(n2) && philosophers[n2].stick_right)
		{
			drop_stick(n2);
			philosophers[n2].stick_right = 0;
		}
		time(&t1);
		time(&t2);
		usleep(100);
	}
	philosophers[n1].life -= REST_T;
	update_hungry(&(philosophers[n1]));
	printf("Philosopher %d stop thinking. Life %d\n", n1, philosophers[n1].life);
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
	int	j;
	int ret;

	i = (int *)param;
	j = *i;
	while (no_philo_dead())
	{
		rest(*i);
		if ((ret = check_sticks(j)) == 1)
			think(j);
		else if (ret == 2)
			eat(j);
		usleep(100);
	}
	return (NULL);
}

int    init_philo(void)
{
	int i;

	i = 0;
	while (i < NB_PHILO)
	{
		philosophers[i].nb = i;
		philosophers[i].life = MAX_LIFE;
		philosophers[i].hungry_lvl = LOW;
		philosophers[i].state = REST;
		philosophers[i].stick_right = 0;
		philosophers[i].stick_left = 0;
		pthread_create(&(philosophers[i].thread), NULL, rootine, &philosophers[i].nb);
		sleep(1);
		i++;
	}
	return (1);
}

void	init_stick(void)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
		pthread_mutex_init(&(sticks[i++]), NULL);
}

void	join_philo(void)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
		pthread_join(philosophers[i++].thread, NULL);
}

int	main(void)
{
	init_stick();
	printf("Init stick done\n");
	if (init_philo() == 1)
	{
		printf("Init philo done\n");
		join_philo();
	}
	return (0);
}
