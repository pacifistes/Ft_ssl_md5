/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_njoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:07:42 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/12 15:07:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char *join, char **str, int nbr_str)
{
	int i;
	int j;
	int h;

	if (join == NULL)
		return (NULL);
	i = 0;
	h = 0;
	while (i < nbr_str)
	{
		j = 0;
		while (str[i][j])
		{
			join[h] = str[i][j];
			j++;
			h++;
		}
		i++;
	}
	join[h] = 0;
	return (join);
}

int			ft_size_join(char **str, int *nbr_free, int nbr_str, int *str_free)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < nbr_str)
	{
		j = j + ft_strlen(str[i]);
		if (str_free[i] == 1 && str[i])
			*nbr_free = *nbr_free + 1;
		i++;
	}
	return (j);
}

char		*ft_free_njoin(char **str, int nbr_str, int *str_free)
{
	int		j;
	int		i;
	int		nbr_free;
	char	**tmp;
	char	*join;

	nbr_free = 0;
	j = ft_size_join(str, &nbr_free, nbr_str, str_free);
	tmp = (char**)malloc(sizeof(char*) * (nbr_free + 1));
	join = (char*)malloc(sizeof(char) * (j + 1));
	if (!join || !tmp)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < nbr_str)
		if (str_free[i] == 1 && str[i])
		{
			tmp[j] = str[i];
			j++;
		}
	tmp[j] = 0;
	join = ft_join(join, str, nbr_str);
	free_tab_str(&tmp);
	return (join);
}
