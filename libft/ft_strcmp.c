/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 19:06:45 by mcassagn          #+#    #+#             */
/*   Updated: 2015/02/12 16:53:41 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	char			*s12;
	char			*s22;
	unsigned int	i;

	if (s1 && s2)
	{
		s12 = (char *)s1;
		s22 = (char *)s2;
		i = 0;
		while (s12[i] && s22[i])
		{
			if (s12[i] != s22[i])
				return ((unsigned char)s12[i] - (unsigned char)s22[i]);
			i++;
		}
		return ((unsigned char)s12[i] - (unsigned char)s22[i]);
	}
	return (-1);
}
