/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/06 18:27:12 by mcassagn          #+#    #+#             */
/*   Updated: 2014/06/19 17:16:57 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <string.h>
#include <stdlib.h>

void				*ft_realloc(void *src, size_t new_size)
{
	void			*new;

	if (src == NULL)
		return (malloc(new_size));
	if (new_size == 0)
		return (src);
	if ((new = (void *)malloc(sizeof(char) * (new_size + 1))) == NULL)
		return (NULL);
	ft_memcpy(new, (const void *)src, new_size + 1);
	free(src);
	return (new);
}
