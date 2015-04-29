/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 20:04:33 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 15:37:21 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char		*ft_strndup(const char *s1, int n)
{
	char	*ptr;
	char	*ret;

	if (s1)
	{
		ptr = (char *)malloc(n * sizeof(char) + 1);
		if (ptr == NULL)
			return (NULL);
		ret = ptr;
		while (n--)
			*ptr++ = *s1++;
		*ptr = '\0';
		return (ret);
	}
	return (NULL);
}
