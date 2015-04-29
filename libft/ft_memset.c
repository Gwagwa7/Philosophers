/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:56:28 by mcassagn          #+#    #+#             */
/*   Updated: 2014/04/15 14:29:24 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*b2;

	if (b)
	{
		b2 = b;
		while (len--)
			*b2++ = (unsigned char)c;
		return (b);
	}
	return (NULL);
}
