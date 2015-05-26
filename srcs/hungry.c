/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hungry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 10:33:24 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/26 10:30:48 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	update_hungry(t_philosophers *philo)
{
	int			turns_left;

	turns_left = philo->life / LOSE_PER_TURN;
	if (turns_left <= 1)
		philo->hungry_lvl = CRITICAL;
	else if (turns_left <= 3)
		philo->hungry_lvl = HIGH;
	else if (turns_left <= 5)
		philo->hungry_lvl = MEDIUM;
	else
		philo->hungry_lvl = LOW;
}
