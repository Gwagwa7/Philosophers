/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:06:29 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/22 14:06:57 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <philosophers.h>

int	main(void)
{
	pthread_t	main_thread;

	init_sticks();
	if (init_philo() == 1)
	{
		pthread_create(&main_thread, NULL, main_rootine, NULL);
		pthread_join(main_thread, NULL);
	}
	return (0);
}
