/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 11:46:20 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:31:48 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*sret;
	char	*save_ret;
	char	*save_src;
	size_t	size;

	if (s && f)
	{
		size = ft_strlen((char *)s);
		sret = (char *)malloc((size + 1) * sizeof(char));
		if (sret == NULL)
			return (NULL);
		save_ret = sret;
		save_src = (char *)s;
		while (*save_src)
		{
			*sret = (*f)((save_src - s), (char)*save_src);
			save_src++;
			sret++;
		}
		return (save_ret);
	}
	return (NULL);
}
