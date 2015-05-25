/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rootines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 11:04:12 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/25 18:18:45 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philosophers.h>

void	*main_rootine(void *param)
{
    int	i;
    char *state;
    char *stickL;
    char *stickR;
    char *hungry;
    char *life;
    time_t	t1;
    time_t	t2;

    (void)param;
    i = 0;
    time(&t1);
    time(&t2);
    while (no_philo_dead() && (t2 - t1 <= TIMEOUT))
    {
        while(i < NB_PHILO)
        {
            if(g_philosophers[i].state == 0)
                state = "\x1B[33mThinking\x1B[0m";
            else if (g_philosophers[i].state == 1)
                state = "\x1B[35mResting\x1B[0m";
            else if (g_philosophers[i].state == 2)
                state = "\x1B[36mEating\x1B[0m";
            if (g_philosophers[i].stick_left == 1)
                stickL = "\x1B[32m1\x1B[0m";
            else
                stickL = "\x1B[33m0\x1B[0m";
            if (g_philosophers[i].stick_right == 1)
                stickR = "\x1B[32m1\x1B[0m";
            else
                stickR = "\x1B[33m0\x1B[0m";
            if (g_philosophers[i].hungry_lvl == CRITICAL)
                hungry = "critical";
            if (g_philosophers[i].hungry_lvl == LOW)
                hungry = "low";
            if (g_philosophers[i].hungry_lvl == MEDIUM)
                hungry = "medium";
            if (g_philosophers[i].hungry_lvl == HIGH)
                hungry = "high";
            life = ft_strjoin("\x1B[32m", ft_itoa(g_philosophers[i].life));
            life = 	ft_strjoin(life, "\x1B[0m");
            printf(PHILO, i, state, life, stickL, stickR, hungry);
            i++;
        }
        printf("Time left = %d\n", TIMEOUT - (t2 - t1));
        printf("******************\n");
        i = 0;
        usleep(750000);
        time(&t2);
    }
    if (no_philo_dead())
        ft_putendl(WIN_MESSAGE);
    else
        ft_putendl("You lose");
    return (NULL);
}

static void    philo_main_rootine(t_philosophers *philo)
{
    if (philo->state == EAT)
        rest(philo);
    take_sticks(philo);
    if (philo->hungry_lvl > MEDIUM)
    {
        if (philo->stick_left && philo->stick_right)
            eat(philo);
        else
        {
            set_sticks(philo, 1);
            think(philo);
        }
    }
    else
    {
        if (philo->stick_left && philo->stick_right)
            drop_stick(philo->nb, philo);
        think(philo);
    }
    update_hungry(philo);
    usleep(100);
}

void	*philo_rootine(void *param)
{
    int	j;
    t_philosophers	*philo;

    j = *(int *)param;
    philo = &(g_philosophers[j]);
    pthread_mutex_lock(&g_sticks[j]);
    while (philo->life > 0)
        philo_main_rootine(philo);
    return (NULL);
}
