/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 17:20:15 by mcassagn          #+#    #+#             */
/*   Updated: 2015/03/23 14:03:13 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"
#include <libft.h>

static int			find_nl(char *str)
{
	char			*bak;

	bak = str;
	if (str)
		while (*str)
			if (*str++ == '\n')
				return (str - bak - 1);
	return (-1);
}

static char			*get_next_nl(char **str)
{
	int				pos;
	int				len;
	char			*ret;
	char			*bak;

	if ((pos = find_nl(*str)) == -1)
		return (NULL);
	if (!(ret = malloc((pos + 1) * sizeof(*ret))))
		return (NULL);
	bak = ret;
	while ((ret - bak) < pos)
		*ret++ = *((*str)++);
	*ret = 0;
	len = ft_strlen(*str);
	if (!(ret = malloc(len + 1 * sizeof(*ret))))
		return (NULL);
	while (**str)
		*ret++ = *(++(*str));
	free(*str - len - pos);
	*str = ret - len;
	return (bak);
}

static char			*concat_string(char *old, char *buf, int n)
{
	char			*ret;
	char			*bak;

	if (!(ret = malloc((ft_strlen(old) + n + 1) * sizeof(*ret))))
		return (NULL);
	bak = ret;
	if (old)
		while (*old)
			*ret++ = *old++;
	*(ret + n) = 0;
	free(old - (ret - bak));
	while (n--)
		*(ret + n) = buf[n];
	return (bak);
}

int					get_next_line(const int fd, char **line)
{
	char			*ret;
	int				nb_read;
	static char		*old;
	char			buf[BUFF_SIZE];

	while (!(ret = get_next_nl(&old)))
	{
		nb_read = read(fd, buf, BUFF_SIZE);
		if (!nb_read)
		{
			ret = old;
			old = NULL;
			*line = ret;
			return (0);
		}
		old = concat_string(old, buf, nb_read);
	}
	*line = ret;
	return (1);
}
