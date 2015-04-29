/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 17:34:27 by mcassagn          #+#    #+#             */
/*   Updated: 2015/02/12 16:57:37 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <libft.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	int				i;
	unsigned int	end;
	unsigned int	len2;

	len2 = ft_strlen(s);
	if (!s || start + len > len2 || start > len2 || len > len2)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	end = start + len;
	while (start < end)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
