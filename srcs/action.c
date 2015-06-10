/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:50:22 by mcassagn          #+#    #+#             */
/*   Updated: 2015/06/10 11:57:23 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <philosophers.h>

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
	set_sticks(philo, 0);
	do_loop(EAT_T);
	philo->life = MAX_LIFE;
	drop_sticks(philo);
}

void		rest(t_philosophers *philo)
{
	drop_sticks(philo);
	philo->state = REST;
	do_loop(REST_T);
	philo->life -= REST_T;
}

void		think(t_philosophers *philo)
{
	t_philosophers	*right;
	t_philosophers	*left;
	time_t			t1;
	time_t			t2;

	time(&t1);
	time(&t2);
	left = &(g_philosophers[LEFT(philo->nb)]);
	right = &(g_philosophers[RIGHT(philo->nb)]);
	philo->state = THINK;
	while (t2 - t1 < THINK_T)
	{
		if (left->need_right_stick)
			drop_stick(philo->nb, philo);
		if (right->need_left_stick)
			drop_stick(RIGHT(philo->nb), philo);
		usleep(100);
		time(&t2);
	}
	philo->life -= THINK_T;
}
