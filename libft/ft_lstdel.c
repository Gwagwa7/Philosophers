/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <mcassagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 15:43:02 by mcassagn          #+#    #+#             */
/*   Updated: 2013/12/01 17:21:34 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <string.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*next;
	t_list		*curr;

	curr = *alst;
	while (curr != NULL)
	{
		next = curr->next;
		(*del)(curr->content, curr->content_size);
		free(curr);
		curr = next;
	}
	*alst = NULL;
}
