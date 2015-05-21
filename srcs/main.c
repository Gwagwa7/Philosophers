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
	while (pthread_mutex_trylock(&(sticks[n]))) ;
}

void    update_hungry(t_philosophers *philo)
{
	float	diff_life;
	int 	life_percent;

	diff_life = (float)philo->life / (float)MAX_LIFE;
	life_percent = diff_life * 100;
	if (life_percent <= 33)
		philo->hungry_lvl = HIGH;
	else if (life_percent <= 66)
		philo->hungry_lvl = MID;
	else
		philo->hungry_lvl = LOW;
}

void	join_philo(void)
{
	int	i;
	int ret;

	ret = 0;	
	i = 0;
	while (i < NB_PHILO)
    {
		ret = pthread_join(philosophers[i].thread, NULL);
    	i++;
    }
}

void    eat(int n1)
{
	int n2;
	time_t  t1;
	time_t  t2;

	printf(EATB, n1+1, n1, philosophers[n1].life);
	n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
	philosophers[n1].state = EAT;
    if (philosophers[n1].stick_left == 0)
    {
        take_stick(n1);
        printf("eat> ");
        printf(TAKEL, n1+1, n1);
    }
    if (philosophers[n1].stick_right == 0)
    {
        take_stick(n2);
        printf("eat> ");
        printf(TAKER, n1+1, n1);
    }
	time(&t1);
	time(&t2);
	while (t2 - t1 < EAT_T)
	{
		time(&t2);
		usleep(100);
	}
    if (philosophers[n1].stick_left == 1)
        drop_stick(n1);
    if (philosophers[n1].stick_right == 1)
        drop_stick(n2);
	philosophers[n1].life = MAX_LIFE;
	update_hungry(&(philosophers[n1]));
	printf(EATE, n1+1, n1, philosophers[n1].life);
}

void    rest(int n1)
{
	int n2;
	time_t  t1;
	time_t  t2;

	printf(RESTB, n1+1, philosophers[n1].nb, philosophers[n1].life);
	n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
	if (philosophers[n1].stick_left)
	{
		drop_stick(n1);
		printf("rest> ");
		printf(DROPL, n1+1, n1);
		philosophers[n1].stick_left = 0;
	}
	if (philosophers[n1].stick_right)
	{
		drop_stick(n2);
		printf("rest> ");
		printf(DROPR, n1+1, n1);
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
	printf(RESTE,n1+1, n1, philosophers[n1].life);
}

int		neigbhor_is_hungry(int n1, int n2)
{
	if (philosophers[n1].hungry_lvl <= philosophers[n2].hungry_lvl)
		return (1);
	return (0);
}

void    think(int n1)
{
	int n2;
	time_t  t1;
	time_t  t2;

	printf(THINKB, n1+1, n1, philosophers[n1].life);
	n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
	time(&t1);
	time(&t2);
	while (t2 - t1 < REST_T)
	{
		if (neigbhor_is_hungry(n2, n1) && philosophers[n1].stick_left)
		{
			drop_stick(n1);
			printf("think> ");
			printf(DROPL, n1+1, n1);
			philosophers[n1].stick_left = 0;
		}
		if (neigbhor_is_hungry(n2, n1) && philosophers[n1].stick_right)
		{
			drop_stick(n2);
			printf("think> ");
			printf(DROPR, n1+1, n1);
			philosophers[n1].stick_right = 0;
		}
		time(&t2);
		usleep(100);
	}
	philosophers[n1].life -= REST_T;
	update_hungry(&(philosophers[n1]));
	printf(THINKE, n1+1, n1, philosophers[n1].life);
}

int     no_philo_dead()
{
	 int    i;
	 i = 0;
	 while (i < NB_PHILO)
	 {
		 if (philosophers[i].life < 1)
			 return (0);
		 i++;
	 }
	
	/*if (philosophers[i].life < 1)*/
	/*{*/
		/*printf(DEAD, i+1, i);*/
		/*return (0);*/
	/*}*/
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
		printf("root/check> ");
		printf(TAKEL, n1+1, n1);
		philosophers[n1].stick_left = 1;
		philosophers[left].stick_right = 0;
		nb_stick++;
	}
	else if (philosophers[n1].stick_left)
		nb_stick++;
	if (!philosophers[n1].stick_right && !philosophers[right].stick_left)
	{
		take_stick(right);
		printf("root/check> ");
		printf(TAKER, n1+1, n1);
		philosophers[n1].stick_right = 1;
		philosophers[right].stick_left = 0;
		nb_stick++;
	}
	else if (philosophers[n1].stick_right)
		nb_stick++;
	return (nb_stick);
}

void	*main_rootine(void *param)
{
	int	i;
	
	(void)param;
	i = 0;
	while (no_philo_dead())
	{
		usleep(100);
	}
	return (NULL);
}

void    *rootine(void *param)
{
	int	j;
	int ret;

	j = *(int *)param;
	while (1)
	{
		printf("root> ");
        printf(PHILO, j+1, philosophers[j].nb, philosophers[j].life, philosophers[j].stick_left, philosophers[j].stick_right);
		rest(j);
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
	while (1)
	{
		philosophers[i].nb = i;
		philosophers[i].life = MAX_LIFE;
		philosophers[i].hungry_lvl = LOW;
		printf("Hungry lvl = %d\n", philosophers[i].hungry_lvl);
		philosophers[i].state = REST;
		philosophers[i].stick_right = 0;
		philosophers[i].stick_left = 0;
		pthread_create(&(philosophers[i].thread), NULL, &rootine, &i);
		usleep(1000);
		printf("init> ");
        printf(PHILO ,i+1, philosophers[i].nb, philosophers[i].life, philosophers[i].stick_left, philosophers[i].stick_right);
        if (i == NB_PHILO - 1)
            break ;
		i++;
	}
	return (1);
}

void	init_stick(void)
{
	int	i;
	int ret;

	i = 0;
	while (i < NB_PHILO)
    {
		ret = pthread_mutex_init(&(sticks[i++]), NULL);
		if (ret == 0)
			printf("Mutex successful init for philo %d\n", i);
    }
}

void    *draw_gui(void *param)
{
    int    i;
    (void)param;

    while (42)
    {
        i = 0;
        while (i < NB_PHILO)
        {
            printf("gui> Philo %d; his life %d; stick_left %d; stick_right %d\n", philosophers[i].nb, philosophers[i].life, philosophers[i].stick_left, philosophers[i].stick_right);
            i++;
        }
    }
}



void    join_gui(void)
{
    pthread_t   gui_thread;

	pthread_create(&gui_thread, NULL, draw_gui, NULL);
    pthread_join(gui_thread, NULL);
}

int	main(void)
{
	pthread_t	main_thread;
	init_stick();
	printf("Init stick done\n");
	if (init_philo() == 1)
	{
		pthread_create(&main_thread, NULL, main_rootine, NULL);
		pthread_join(main_thread, NULL);
	}
	return (0);
}
