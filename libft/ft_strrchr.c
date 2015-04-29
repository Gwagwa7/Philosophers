/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:41:49 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:32:16 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char			*last;

	last = NULL;
	while (1)
	{
		if (*s == c)
			last = (char *)s;
		if (*s == '\0')
			return (char *)last;
		s++;
	}
}
