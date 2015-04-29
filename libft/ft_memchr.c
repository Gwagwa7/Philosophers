/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 14:09:10 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:27:58 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*s2;

	if (s)
	{
		s2 = (unsigned char *)s;
		while (n--)
		{
			if (*s2 == (unsigned char)c)
				return (void *)s2;
			s2++;
		}
	}
	return (NULL);
}
