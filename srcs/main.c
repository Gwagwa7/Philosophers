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
	if (life_percent <= 10)
		philo->hungry_lvl = CRITICAL;
	else if (life_percent <= 33)
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

	// printf(EATB, n1+1, n1, philosophers[n1].life);
	n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
	philosophers[n1].state = EAT;
    if (philosophers[n1].stick_left == 0)
    {
        take_stick(n1);
        philosophers[n1].stick_left = 1;
        /*printf("eat> ");*/
        /*printf(TAKEL, n1+1, n1);*/
    }
    if (philosophers[n1].stick_right == 0)
    {
        take_stick(n2);
        philosophers[n1].stick_right = 1;
        /*printf("eat> ");*/
        /*printf(TAKER, n1+1, n1);*/
    }
	time(&t1);
	time(&t2);
	while (t2 - t1 < EAT_T)
	{
		time(&t2);
		usleep(100);
	}
    drop_stick(n1);
    philosophers[n1].stick_left = 0;
    drop_stick(n2);
    philosophers[n1].stick_right = 0;
	philosophers[n1].life = MAX_LIFE;
	update_hungry(&(philosophers[n1]));
	// printf(EATE, n1+1, n1, philosophers[n1].life);
}

void    rest(int n1)
{
	int n2;
	time_t  t1;
	time_t  t2;

	// printf(RESTB, n1+1, philosophers[n1].nb, philosophers[n1].life);
	n2 = (n1 == NB_PHILO) ? 0 : n1 + 1;
		drop_stick(n1);
		philosophers[n1].stick_left = 0;
		drop_stick(n2);
		philosophers[n1].stick_right = 0;
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
	// printf(RESTE,n1+1, n1, philosophers[n1].life);
}

int		neigbhor_is_hungry(int n1, int n2)
{
	if (philosophers[n1].hungry_lvl <= philosophers[n2].hungry_lvl)
		return (1);
	if (philosophers[n1].hungry_lvl == CRITICAL)
		return (1);
	return (0);
}

void    think(int n1)
{
	int left;
	int right;
	time_t  t1;
	time_t  t2;

	/*printf(THINKB, n1+1, n1, philosophers[n1].life);*/
	right = (n1 == NB_PHILO) ? 0 : n1 + 1;
	left = (n1 == 0) ? NB_PHILO : n1 - 1;
	time(&t1);
	time(&t2);
	philosophers[n1].state = THINK;
	while (t2 - t1 < REST_T)
	{
		if (neigbhor_is_hungry(right, n1) && philosophers[n1].stick_right)
		{
			drop_stick(n1);
			 /*printf("think> ");*/
			/*printf(DROPL, n1+1, n1);*/
			philosophers[n1].stick_right = 0;
		}
		if (neigbhor_is_hungry(left, n1) && philosophers[left].stick_left)
		{
			drop_stick(right);
			/*printf("think> ");*/
			/*printf(DROPR, n1+1, n1);*/
			philosophers[n1].stick_left = 0;
		}
		time(&t2);
		usleep(100);
	}
	philosophers[n1].life -= REST_T;
	update_hungry(&(philosophers[n1]));
	// printf(THINKE, n1+1, n1, philosophers[n1].life);
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
		// printf(DEAD, i+1, i);
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
		if (philosophers[left].state == THINK)
		{
			philosophers[left].stick_right = 0;
			drop_stick(right);
		}
		take_stick(right);
		philosophers[n1].stick_left = 1;
		nb_stick++;
	}
	else if (philosophers[n1].stick_left)
		nb_stick++;
	if (!philosophers[n1].stick_right && !philosophers[right].stick_left)
	{
		if (philosophers[right].state == THINK)
		{
			philosophers[right].stick_left = 0;
			drop_stick(n1);
		}
		take_stick(n1);
		philosophers[n1].stick_right = 1;
		nb_stick++;
	}
	else if (philosophers[n1].stick_right)
		nb_stick++;
	return (nb_stick);
}

void	*main_rootine(void *param)
{
	int	i;
	char *state;
	char *stickL;
	char *stickR;
	char *life;
	time_t	t1;
	time_t	t2;
	
	(void)param;
	i = 0;
	time(&t1);
	time(&t2);
	while (no_philo_dead() && (t2 - t1 <= TIMEOUT))
	{
		printf("******************\n");
		while(i < NB_PHILO)
		{
			if(philosophers[i].state == 0)
				state = "\x1B[33mThinking\x1B[0m";
			else if (philosophers[i].state == 1)
				state = "\x1B[35mResting\x1B[0m";
			else if (philosophers[i].state == 2)
				state = "\x1B[36mEating\x1B[0m";
			else
				state = "\x1B[31mStarving\x1B[0m";
			if (philosophers[i].stick_left == 1)
				stickL = "\x1B[32m1\x1B[0m";
			else
				stickL = "\x1B[33m0\x1B[0m";
			if (philosophers[i].stick_right == 1)
				stickR = "\x1B[32m1\x1B[0m";
			else
				stickR = "\x1B[33m0\x1B[0m";
			life = ft_strjoin("\x1B[32m", ft_itoa(philosophers[i].life));
			life = 	ft_strjoin(life, "\x1B[0m");
			printf(PHILO, i, state, life, stickL, stickR);
			i++;
		}
		i = 0;
		usleep(1000);
		time(&t2);
	}
	return (NULL);
}

void    *rootine(void *param)
{
	int	j;
	int ret;
	int	flag;

	j = *(int *)param;
	flag = 0;
	while (1)
	{
		if (j % 2 && !flag)
		{
			think(j);
			flag = 1;
		}
		else
			rest(j);
		ret = check_sticks(j);
		printf("Philo %d Ret = %d\n", j, ret);
		if (ret == 1)
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
		philosophers[i].state = THINK;
		philosophers[i].stick_right = 0;
		philosophers[i].stick_left = 1;
		pthread_create(&(philosophers[i].thread), NULL, &rootine, &i);
		usleep(1000);
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
            // printf("gui> Philo %d; his life %d; stick_left %d; stick_right %d\n", philosophers[i].nb, philosophers[i].life, philosophers[i].stick_left, philosophers[i].stick_right);
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
	// printf("Init stick done\n");
	if (init_philo() == 1)
	{
		pthread_create(&main_thread, NULL, main_rootine, NULL);
		pthread_join(main_thread, NULL);
	}
	return (0);
}
