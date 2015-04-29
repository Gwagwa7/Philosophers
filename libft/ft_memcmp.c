/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 14:15:41 by mcassagn          #+#    #+#             */
/*   Updated: 2015/02/12 16:51:53 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	char			*s12;
	char			*s22;
	unsigned int	i;

	if (s1 && s2)
	{
		s12 = (char *)s1;
		s22 = (char *)s2;
		i = 0;
		while (i < n)
		{
			c1 = s12[i];
			c2 = s22[i];
			if (c1 != c2)
				return (c1 - c2);
			i++;
		}
		return (0);
	}
	return (-1);
}
