/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 12:04:25 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:28:43 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*s12;
	const char	*s22;

	if (s1 && s2)
	{
		s12 = s1;
		s22 = s2;
		while (n--)
			*s12++ = *s22++;
		return (s1);
	}
	return (NULL);
}
