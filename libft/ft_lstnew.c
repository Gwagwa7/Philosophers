/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 15:07:30 by mcassagn          #+#    #+#             */
/*   Updated: 2015/01/16 15:41:07 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <string.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new_lst;

	if ((new_lst = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content)
	{
		new_lst->content = (void *)malloc(content_size * sizeof(char));
		ft_memcpy(new_lst->content, content, content_size);
	}
	else
	{
		new_lst->content = NULL;
		new_lst->content_size = 0;
	}
	new_lst->next = NULL;
	return (new_lst);
}
