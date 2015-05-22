/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:50:22 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/22 17:55:38 by mcassagn         ###   ########.fr       */
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
	if (!g_philosophers[philo].stick_left)
	{
		take_stick(philo);
		g_philosophers[philo].stick_left = 1;
	}
	if (!g_philosophers[philo].stick_right)
	{
		take_stick(RIGHT(philo));
		g_philosophers[philo].stick_right = 1;
	}
	do_loop(EAT_T);
	if (g_philosophers[philo].stick_left)
		drop_stick(philo);
	g_philosophers[philo].stick_left = 0;
	if (g_philosophers[philo].stick_right)
		drop_stick(RIGHT(philo));
	g_philosophers[philo].stick_right = 0;
	g_philosophers[philo].life = MAX_LIFE;
	update_hungry(&(g_philosophers[philo]));
}

void		rest(int philo)
{
	if (g_philosophers[philo].stick_left)
		drop_stick(philo);
	g_philosophers[philo].stick_left = 0;
	if (g_philosophers[philo].stick_right)
		drop_stick(RIGHT(philo));
	g_philosophers[philo].stick_right = 0;
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
		if (g_philosophers[philo].stick_right\
				&& neighbor_is_hungry(RIGHT(philo), philo)\
				&& g_philosophers[RIGHT(philo)].state == REST)
		{
			drop_stick(RIGHT(philo));
			g_philosophers[philo].stick_right = 0;
		}
		else if (g_philosophers[philo].stick_left\
				&& neighbor_is_hungry(LEFT(philo), philo)
				&& g_philosophers[LEFT(philo)].state == REST)
		{
			drop_stick(philo);
			g_philosophers[philo].stick_left = 0;
		}
		usleep(100);
		time(&t2);
	}
	g_philosophers[philo].life -= THINK_T;
	update_hungry(&(g_philosophers[philo]));
}
