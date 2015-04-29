/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 16:47:13 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:34:41 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	char	*s12;
	char	*s22;

	if (s1 && s2)
	{
		s12 = (char *)s1;
		s22 = (char *)s2;
		while (n--)
		{
			if (*s12 != *s22)
				return (0);
			s12++;
			s22++;
		}
		return (1);
	}
	return (0);
}
