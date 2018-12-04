/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:53:41 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/22 12:32:02 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	insert_at_begin(t_datas **datas, t_datas **tmp)
{
	t_datas *temp;

	temp = *datas;
	if (!temp)
	{
		(*tmp)->next = NULL;
		*datas = *tmp;
	}
	else
	{
		(*tmp)->next = temp;
		*datas = *tmp;
	}
}

void	insert_at_end(t_datas **datas, t_datas **tmp)
{
	t_datas *temp;

	temp = *datas;
	if (!temp)
	{
		(*tmp)->next = NULL;
		*datas = *tmp;
	}
	else
	{
		while (temp && temp->next)
			temp = temp->next;
		(*tmp)->next = NULL;
		temp->next = *tmp;
	}
}

void	insert_data(t_datas **datas, char **str, int is_string, int at_end)
{
	t_datas		*tmp;

	tmp = ft_memalloc(sizeof(t_datas));
	if (!tmp)
		return ;
	tmp->str = str;
	tmp->is_file = (is_string == 0) ? 1 : 0;
	if (at_end)
		insert_at_end(datas, &tmp);
	else
		insert_at_begin(datas, &tmp);
}

void	free_datas(t_datas **datas)
{
	t_datas *tmp;

	while (*datas)
	{
		tmp = *datas;
		*datas = (*datas)->next;
		free(tmp);
	}
}
