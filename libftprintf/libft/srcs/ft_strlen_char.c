/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 00:35:47 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/07 00:35:51 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_char(char *str, char c)
{
	int i;
	int compteur;

	i = 0;
	compteur = 0;
	while (str[i])
	{
		if (str[i] == c)
			compteur++;
		i++;
	}
	return (compteur);
}
