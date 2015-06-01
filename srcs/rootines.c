/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rootines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 11:04:12 by mcassagn          #+#    #+#             */
/*   Updated: 2015/06/01 11:05:38 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philosophers.h>

void			*main_rootine(void *param)
{
	time_t	t1;
	time_t	t2;
	WINDOW	*info;
	WINDOW	*graph;
	WINDOW	*philo[NB_PHILO];

	(void)param;
	time(&t1);
	time(&t2);
	init_display();
	while (no_philo_dead() && (t2 - t1 <= TIMEOUT))
	{
		initndisplay_graph(&graph, &info);
		init_philo_win(philo, graph);
		display_info(&info);
		display_philo(philo, 0);
		time(&t2);
	}
	finish(0);
	if (no_philo_dead())
		ft_putendl(WIN_MESSAGE);
	else
		ft_putendl("You lose");
	return (NULL);
}

static void		philo_main_rootine(t_philosophers *philo)
{
	if (philo->state == EAT)
		rest(philo);
	take_sticks(philo);
	if (philo->stick_left && philo->stick_right)
		eat(philo);
	else
	{
		set_sticks(philo, 1);
		if (philo->stick_left && philo->stick_right)
			drop_stick(philo->nb, philo);
		think(philo);
	}
	update_hungry(philo);
	usleep(100);
}

void			*philo_rootine(void *param)
{
	int				j;
	t_philosophers	*philo;

	j = *(int *)param;
	philo = &(g_philosophers[j]);
	pthread_mutex_lock(&g_sticks[j]);
	while (philo->life > 0)
		philo_main_rootine(philo);
	return (NULL);
}
