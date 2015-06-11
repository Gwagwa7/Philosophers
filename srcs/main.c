/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:06:29 by mcassagn          #+#    #+#             */
/*   Updated: 2015/06/10 12:00:26 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <philosophers.h>

int	main(void)
{
	pthread_t	main_thread;

	if (NB_PHILO <= 3)
		write(1, "NB_PHILO must be greater than 3\n", 32);
	else
	{
		init_sticks();
		if (init_philo() == 1)
		{
			pthread_create(&main_thread, NULL, main_rootine, NULL);
			pthread_join(main_thread, NULL);
		}
	}
	return (0);
}
