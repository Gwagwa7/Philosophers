/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sticks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:20:50 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/22 17:41:59 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philosophers.h>
#include <stdio.h>

void	drop_stick(int stick)
{
	printf("Unlock : %d\n", pthread_mutex_unlock(&(g_sticks[stick])));
}

void	take_stick(int stick)
{
	while (pthread_mutex_trylock(&(g_sticks[stick])))
		;
}

int		check_left_stick(int philo)
{
	if (!g_philosophers[philo].stick_left)
	{
		if (g_philosophers[LEFT(philo)].stick_right && g_philosophers[LEFT(philo)].state == THINK)
		{
			drop_stick(philo);
			g_philosophers[LEFT(philo)].stick_right = 0;
		}
		if (!g_philosophers[LEFT(philo)].stick_right)
		{
			take_stick(philo);
			g_philosophers[philo].stick_left = 1;
			return (1);
		}
		return (0);
	}
	return (1);
}

int		check_sticks(int philo)
{
	int	nb_sticks;

	nb_sticks = check_left_stick(philo);
	if (!g_philosophers[philo].stick_right)
	{
		if (g_philosophers[RIGHT(philo)].stick_left && g_philosophers[RIGHT(philo)].state == THINK)
		{
			drop_stick(RIGHT(philo));
			g_philosophers[RIGHT(philo)].stick_left = 0;
		}
		if (!g_philosophers[RIGHT(philo)].stick_left)
		{
			take_stick(RIGHT(philo));
			g_philosophers[philo].stick_right = 1;
			nb_sticks++;
		}
	}
	else
		nb_sticks++;
	return (nb_sticks);
}

int		init_sticks(void)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		pthread_mutex_init(&(g_sticks[i]), NULL);
		++i;
	}
	return (1);
}
