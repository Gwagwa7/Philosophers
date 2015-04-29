/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:41:49 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:30:43 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;

	if (s)
	{
		ch = (unsigned char)c;
		while (42)
		{
			if (*s == ch)
				return ((char *)s);
			if (!*s)
				return ((char *)NULL);
			s++;
		}
	}
	return ((char *)NULL);
}
