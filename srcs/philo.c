/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 11:11:02 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 16:53:55 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <philosophers.h>

void	join_philo(void)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		pthread_join(g_philosophers[i].thread, NULL);
		i++;
	}
}

int		no_philo_dead(void)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		if (g_philosophers[i].life < 1)
			return (0);
		i++;
	}
	return (1);
}

int		init_philo(void)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		g_philosophers[i].nb = i;
		g_philosophers[i].life = MAX_LIFE;
		g_philosophers[i].hungry_lvl = LOW;
		g_philosophers[i].state = REST;
		g_philosophers[i].stick_right = 0;
		g_philosophers[i].stick_left = 0;
		pthread_create(&(g_philosophers[i].thread), NULL, &philo_rootine, &i);
		usleep(1000);
		i++;
	}
	return (1);
}
