/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rootines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 11:04:12 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/22 18:27:44 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philosophers.h>

void	*main_rootine(void *param)
{
	int	i;
	char *state;
	char *stickL;
	char *stickR;
	char *hungry;
	char *life;
	time_t	t1;
	time_t	t2;

	(void)param;
	i = 0;
	time(&t1);
	time(&t2);
	while (no_philo_dead() && (t2 - t1 <= TIMEOUT))
	{
		while(i < NB_PHILO)
		{
			if(g_philosophers[i].state == 0)
				state = "\x1B[33mThinking\x1B[0m";
			else if (g_philosophers[i].state == 1)
				state = "\x1B[35mResting\x1B[0m";
			else if (g_philosophers[i].state == 2)
				state = "\x1B[36mEating\x1B[0m";
			if (g_philosophers[i].stick_left == 1)
				stickL = "\x1B[32m1\x1B[0m";
			else
				stickL = "\x1B[33m0\x1B[0m";
			if (g_philosophers[i].stick_right == 1)
				stickR = "\x1B[32m1\x1B[0m";
			else
				stickR = "\x1B[33m0\x1B[0m";
			if (g_philosophers[i].hungry_lvl == CRITICAL)
				hungry = "critical";
			if (g_philosophers[i].hungry_lvl == LOW)
				hungry = "low";
			if (g_philosophers[i].hungry_lvl == MID)
				hungry = "mid";
			if (g_philosophers[i].hungry_lvl == HIGH)
				hungry = "high";
			life = ft_strjoin("\x1B[32m", ft_itoa(g_philosophers[i].life));
			life = 	ft_strjoin(life, "\x1B[0m");
			printf(PHILO, i, state, life, stickL, stickR, hungry);
			i++;
		}
		printf("******************\n");
		i = 0;
		usleep(1000);
		time(&t2);
	}
	if (no_philo_dead())
		ft_putendl(WIN_MESSAGE);
	else
		ft_putendl("You lose");
	return (NULL);
}

void	steal_stick(int stick)
{
	if (g_philosophers[stick].stick_left && g_philosophers[stick].state == THINK)
	{
		g_philosophers[stick].stick_left = 0;
		pthread_mutex_unlock(&(g_sticks[stick]));
	}
}

void	*philo_rootine(void *param)
{
	int	j;
	int	ret;
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
		if (ret == 1)
			think(j);
		else if (ret == 2 && (!neighbor_is_hungry(LEFT(j), j) || !neighbor_is_hungry(RIGHT(j), j)))
			eat(j);
		else
		{
			drop_stick(j);
			g_philosophers[j].stick_left = 0;
		}
		usleep(100);
	}
	return (NULL);
}
