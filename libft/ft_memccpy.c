/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 13:17:59 by mcassagn          #+#    #+#             */
/*   Updated: 2015/01/28 16:08:37 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char			*s12;
	const char		*s22;
	unsigned int	i;

	if (s1 && s2)
	{
		s12 = s1;
		s22 = s2;
		i = 0;
		while (i < n)
		{
			if (c == s22[i])
				return (void *)(&(s12[i + 1]));
			s12[i] = s22[i];
			i++;
		}
	}
	return (NULL);
}
