/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:22:42 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 15:51:12 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t		ft_strlen(char const *s)
{
	char	*save;

	if (s)
	{
		save = (char *)s;
		while (*save)
			++save;
		return (save - s);
	}
	return (0);
}
