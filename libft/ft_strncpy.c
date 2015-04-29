/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:57:14 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 15:36:41 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strncpy(char *s1, const char *s2, size_t n)
{
	char	*tmp;

	if (s1 && s2)
	{
		if (!n)
			return (s1);
		tmp = s1;
		while (n--)
			if (*s2)
				*s1++ = *s2++;
			else
				*s1++ = 0;
		return (tmp);
	}
	return (NULL);
}
