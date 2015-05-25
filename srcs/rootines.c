/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rootines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 11:04:12 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 15:02:43 by mcassagn         ###   ########.fr       */
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
			if (g_philosophers[i].hungry_lvl == MEDIUM)
				hungry = "medium";
			if (g_philosophers[i].hungry_lvl == HIGH)
				hungry = "high";
			life = ft_strjoin("\x1B[32m", ft_itoa(g_philosophers[i].life));
			life = 	ft_strjoin(life, "\x1B[0m");
			printf(PHILO, i, state, life, stickL, stickR, hungry);
			i++;
		}
		printf("******************\n");
		i = 0;
		usleep(500000);
		time(&t2);
	}
	if (no_philo_dead())
		ft_putendl(WIN_MESSAGE);
	else
		ft_putendl("You lose");
	return (NULL);
}

int		steal_stick(int stick, t_philosophers *victim, t_philosophers *thief)
{
	pthread_mutex_unlock(&(g_sticks[stick]));
	if (victim->nb == stick)
		victim->stick_left = 0;
	else
		victim->stick_right = 0;
	pthread_mutex_lock(&(g_sticks[stick]));
	if (victim->nb == stick)
		thief->stick_right = 1;
	else
		thief->stick_left = 1;
	return (1);
}

int		can_steal(int stick, t_philosophers *victim, t_philosophers *me)
{
	int	*stick_used;

	if (stick == victim->nb)
		stick_used = &victim->stick_left;
	else
		stick_used = &victim->stick_right;
	if (!*stick_used)
		return (1);
	if (!neighbor_is_hungry(victim, me) || victim->state == THINK)
		return (1);
	return (0);
}

void	*philo_rootine(void *param)
{
	int	j;
	int	ret;
	int	flag;
	int	nb_sticks;
	t_philosophers	*philo;
	t_philosophers	*left_philo;
	t_philosophers	*right_philo;

	j = *(int *)param;
	philo = &(g_philosophers[j]);
	left_philo = &(g_philosophers[LEFT(j)]);
	right_philo = &(g_philosophers[RIGHT(j)]);
	flag = 0;
	while (1)
	{
		nb_sticks = philo->stick_left + philo->stick_right;;
		if (flag)
		{
		if (!philo->stick_right && !right_philo->stick_left && take_stick(RIGHT(j), philo))
		{
			nb_sticks++;
			if (!philo->stick_left && !left_philo->stick_right && take_stick(j, philo) && !neighbor_is_hungry(left_philo, philo))
				nb_sticks++;
		}
		else if (!philo->stick_left && !right_philo->stick_left && take_stick(j, philo))
			nb_sticks++;
		if (nb_sticks == 2)
			eat(j);
		else if (nb_sticks == 1)
			think(j);
		if (philo->stick_left)
			drop_stick(j, philo);
		if (philo->stick_right)
			drop_stick(RIGHT(j), philo);
		rest(j);
		}
		else
		{
			think(j);
			flag = 1;
		}
		usleep(100);
	}
	return (NULL);
}
