/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hungry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:33:24 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/22 18:31:32 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosophers.h>

void	update_hungry(t_philosophers *philo)
{
	int			diff_life;

	diff_life = (int)(((float)philo->life / (float)MAX_LIFE) * 100);
	if (diff_life <= 70)
		philo->hungry_lvl = CRITICAL;
	else if (diff_life <= 70)
		philo->hungry_lvl = LOW;
	else if (diff_life <= 80)
		philo->hungry_lvl = MID;
	else
		philo->hungry_lvl = HIGH;
}

int		neighbor_is_hungry(int neighbor, int me)
{
	if (g_philosophers[neighbor].hungry_lvl > g_philosophers[me].hungry_lvl)
		return (1);
	if (g_philosophers[neighbor].hungry_lvl == CRITICAL)
		return (1);
	return (0);
}
