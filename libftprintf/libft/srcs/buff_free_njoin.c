/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_free_njoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 21:25:33 by bbrunell          #+#    #+#             */
/*   Updated: 2017/10/21 14:17:11 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buff_free_njoin(char **str, t_buffer *b, int nbr_str, int *str_free)
{
	int		i;
	int		j;
	int		nbr_free;
	char	**tmp;

	i = -1;
	nbr_free = 0;
	while (++i < nbr_str)
		if (str_free[i] == 1)
			nbr_free++;
	j = -1;
	tmp = (char**)malloc(sizeof(char*) * (nbr_free + 1));
	if (!tmp)
		return ;
	i = -1;
	while (++i < nbr_str)
		while (str[i] && i < nbr_str)
		{
			if (str_free[i] == 1 && ++j < nbr_str)
				tmp[j] = str[i];
			buff_join(str[i], b);
			i++;
		}
	tmp[j] = 0;
	free_tab_str(&tmp);
}
