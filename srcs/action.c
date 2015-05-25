/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:50:22 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 11:34:59 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <philosophers.h>

#include <stdio.h>

static void	do_loop(int time_max)
{
	time_t	t1;
	time_t	t2;

	time(&t1);
	time(&t2);
	while (t2 - t1 < time_max)
	{
		usleep(100);
		time(&t2);
	}
}

void		eat(int philo)
{
	g_philosophers[philo].state = EAT;
	do_loop(EAT_T);
	g_philosophers[philo].life = MAX_LIFE;
	update_hungry(&(g_philosophers[philo]));
}

void		rest(int philo)
{
	g_philosophers[philo].state = REST;
	do_loop(REST_T);
	g_philosophers[philo].life -= REST_T;
	update_hungry(&(g_philosophers[philo]));
}

void		think(int philo)
{
	time_t	t1;
	time_t	t2;

	time(&t1);
	time(&t2);
	g_philosophers[philo].state = THINK;
	while (t2 - t1 < THINK_T)
	{
		usleep(100);
		time(&t2);
	}
	g_philosophers[philo].life -= THINK_T;
	update_hungry(&(g_philosophers[philo]));
}
