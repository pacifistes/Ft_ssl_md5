/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 10:47:37 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 13:53:38 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *a;
	t_list *b;

	a = *alst;
	while (a)
	{
		b = a->next;
		del(a->content, a->content_size);
		free(a);
		a = b;
	}
	*alst = NULL;
}
