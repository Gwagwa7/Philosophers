/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sticks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:20:50 by mcassagn          #+#    #+#             */
/*   Updated: 2015/06/10 11:59:07 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philosophers.h>

void	take_stick(int stick, t_philosophers *philo)
{
	if (!(pthread_mutex_trylock(&(g_sticks[stick]))))
	{
		if (philo->nb == stick)
			philo->stick_left = 1;
		else
			philo->stick_right = 1;
	}
}

void	take_sticks(t_philosophers *philo)
{
	take_stick(philo->nb, philo);
	take_stick(RIGHT(philo->nb), philo);
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

void	set_sticks(t_philosophers *philo, int i)
{
	if (i)
	{
		if (!philo->stick_left)
			philo->need_left_stick = 1;
		if (!philo->stick_right)
			philo->need_right_stick = 1;
	}
	else
		philo->need_left_stick = 0;
	philo->need_right_stick = 0;
}
