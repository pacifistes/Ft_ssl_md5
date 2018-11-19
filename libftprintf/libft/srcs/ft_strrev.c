/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:10:42 by bbrunell          #+#    #+#             */
/*   Updated: 2016/11/22 16:55:31 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	int		compteur;
	char	c;

	compteur = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		i++;
		compteur++;
	}
	compteur--;
	i--;
	while (compteur != 0 && compteur != 1)
	{
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		i--;
		j++;
		compteur = compteur - 2;
	}
	return (str);
}
