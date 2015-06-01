/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_stick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 11:06:13 by mschmit           #+#    #+#             */
/*   Updated: 2015/06/01 11:07:55 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	drop_stick(int stick, t_philosophers *philo)
{
	int	*stick_used;

	if (philo->nb == stick)
		stick_used = &philo->stick_left;
	else
		stick_used = &philo->stick_right;
	if (!*stick_used)
		return ;
	*stick_used = 0;
	pthread_mutex_unlock(&(g_sticks[stick]));
}

void	drop_sticks(t_philosophers *philo)
{
	drop_stick(philo->nb, philo);
	drop_stick(RIGHT(philo->nb), philo);
}
