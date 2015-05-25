/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:50:22 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 18:03:09 by mcassagn         ###   ########.fr       */
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

void		eat(t_philosophers *philo)
{
	philo->state = EAT;
	do_loop(EAT_T);
	philo->life = MAX_LIFE;
	update_hungry(philo);
}

void		rest(t_philosophers *philo)
{
	if (philo->stick_left)
		drop_stick(philo->nb, philo);
	if (philo->stick_right)
		drop_stick(RIGHT(philo->nb), philo);
	philo->state = REST;
	do_loop(REST_T);
	philo->life -= REST_T;
	update_hungry(philo);
}

void		think(t_philosophers *philo)
{
	t_philosophers	*right;
	t_philosophers	*left;
	time_t	t1;
	time_t	t2;

	time(&t1);
	time(&t2);
	left = &(g_philosophers[LEFT(philo->nb)]);
	right = &(g_philosophers[RIGHT(philo->nb)]);
	philo->state = THINK;
	while (t2 - t1 < THINK_T)
	{
		if (neighbor_is_hungry(left, philo))
			drop_stick(philo->nb, philo);
		if (neighbor_is_hungry(right, philo))
			drop_stick(RIGHT(philo->nb), philo);
		usleep(100);
		time(&t2);
	}
	philo->life -= THINK_T;
	update_hungry(philo);
}
