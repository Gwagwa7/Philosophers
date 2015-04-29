/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 15:33:17 by mcassagn          #+#    #+#             */
/*   Updated: 2015/02/12 16:53:29 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <libft.h>

char			*ft_strtrim(char const *s)
{
	size_t		len;
	int			size;
	int			i;
	char		*new_str;

	len = ft_strlen(s);
	size = len + 1;
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
	{
		i++;
		size--;
	}
	while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n' || s[len] == '\0')
	{
		len--;
		size--;
	}
	if (size < 0)
		return (ft_strnew(1));
	if (!(new_str = ft_strnew(size + 1)))
		return (NULL);
	ft_strncpy(new_str, s + i, size);
	new_str[size + 1] = '\0';
	return (new_str);
}
