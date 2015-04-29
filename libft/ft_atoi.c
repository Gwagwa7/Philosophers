/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 17:20:22 by mcassagn          #+#    #+#             */
/*   Updated: 2015/03/23 13:32:47 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_atoi(char *str)
{
	int		minus;
	int		res;

	res = 0;
	minus = 1;
	if (str)
	{
		while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
				|| *str == '\r' || *str == '\f' || *str == '\v'))
			str++;
		if (*str == '-' && str++)
			minus = -1;
		else if (*str == '+' && str++)
			minus = 1;
		while (*str && *str >= '0' && *str <= '9')
			res = res * 10 + (*str++ - '0');
	}
	return (minus * res);
}
