/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:34:36 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:31:05 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*s2;

	if (s1)
	{
		size = ft_strlen(s1);
		if ((s2 = (char *)malloc((size + 1) * sizeof(char))) == NULL)
			return (NULL);
		ft_strcpy(s2, s1);
		return (s2);
	}
	return (NULL);
}
