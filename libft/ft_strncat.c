/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:32:11 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 15:36:59 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*s12;
	const char	*s22;

	if (s1 && s2)
	{
		s12 = s1;
		s22 = s2;
		while (*s12)
			s12++;
		while (n-- && (*s12++ = *s22++))
			;
		*s12 = '\0';
		return (s1);
	}
	return (NULL);
}
