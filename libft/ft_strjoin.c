/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 14:43:23 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:38:02 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*save_ret;
	char	*save_s1;
	char	*save_s2;
	size_t	size;

	if (s1 && s2)
	{
		save_s1 = (char *)s1;
		save_s2 = (char *)s2;
		size = (ft_strlen(save_s1) + ft_strlen(save_s2) + 1);
		ret = (char *)malloc(size * (sizeof(char)));
		if (ret == NULL)
			return (NULL);
		save_ret = ret;
		while (*save_s1)
			*ret++ = *save_s1++;
		while (*save_s2)
			*ret++ = *save_s2++;
		*ret = '\0';
		return (save_ret);
	}
	return (NULL);
}
