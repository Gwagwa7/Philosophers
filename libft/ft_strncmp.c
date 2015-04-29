/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:31:33 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:31:55 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*s12;
	char	*s22;

	if (s1 && s2)
	{
		s12 = (char *)s1;
		s22 = (char *)s2;
		if (n == 0)
			return (0);
		while (--n && *s12 && *s22 && *s12 == *s22)
		{
			s12++;
			s22++;
		}
		return ((unsigned char)*s12 - (unsigned char)*s22);
	}
	return (-1);
}
