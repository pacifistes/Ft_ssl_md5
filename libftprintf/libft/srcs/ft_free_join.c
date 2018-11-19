/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 00:38:02 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/07 00:38:04 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char *join, const char *s1, const char *s2)
{
	int i;
	int j;

	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

char		*ft_free_join(char *s1, char *s2)
{
	int		j;
	char	*join;
	char	*tmp;

	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		j = ft_strlen(s2);
	else if (s2 == NULL)
		j = ft_strlen(s1);
	else
		j = ft_strlen(s1) + ft_strlen(s2);
	tmp = s1;
	join = (char*)malloc(sizeof(char) * (j + 1));
	if (!join)
		return (NULL);
	join = ft_join(join, s1, s2);
	ft_strdel(&tmp);
	return (join);
}
