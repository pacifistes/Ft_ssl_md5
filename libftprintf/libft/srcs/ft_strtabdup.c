/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:37:42 by bbrunell          #+#    #+#             */
/*   Updated: 2017/08/13 17:38:08 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtabdup(char **str)
{
	int		i;
	char	**tab;
	int		j;

	i = 0;
	if (str == 0)
		return (NULL);
	while (str[i])
		i++;
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (tab);
	j = 0;
	while (j < i)
	{
		tab[j] = ft_strdup(str[j]);
		j++;
	}
	tab[j] = 0;
	return (tab);
}
