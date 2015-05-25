/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hungry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:33:24 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 14:44:47 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosophers.h>

void	update_hungry(t_philosophers *philo)
{
	int			turns_left;

	turns_left = philo->life / LOSE_PER_TURN;
	if (turns_left <= 4)
		philo->hungry_lvl = CRITICAL;
	else if (turns_left <= 5)
		philo->hungry_lvl = HIGH;
	else if (turns_left <= 6)
		philo->hungry_lvl = MEDIUM;
	else
		philo->hungry_lvl = LOW;
}

int		neighbor_is_hungry(t_philosophers *neighbor, t_philosophers *me)
{
	if (me->life > neighbor->life)
		return (1);
	return (0);
}

int		neighbors_is_hungry(t_philosophers *n1, t_philosophers *n2, t_philosophers *me)
{
	if (neighbor_is_hungry(n1, me) || neighbor_is_hungry(n2, me))
		return (1);
	return (0);
}
