/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 21:37:50 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 22:38:29 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		is_hexa(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A'
		&& str[i] <= 'F') || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

static uint64_t	atohex(char *str)
{
	int			i;
	int			lenght;
	uint64_t	coef;
	uint64_t	result;

	if (!str || !is_hexa(str))
		return (0);
	i = 0;
	coef = 1;
	result = 0;
	lenght = ft_strlen(str);
	while (i < lenght)
	{
		if (ft_isdigit(str[(lenght - i) - 1]))
			result += (str[(lenght - i) - 1] - '0') * coef;
		else if (ft_islower(str[(lenght - i) - 1]))
			result += (str[(lenght - i) - 1] - 'a' + 10) * coef;
		else
			result += (str[(lenght - i) - 1] - 'A' + 10) * coef;
		coef = coef * 16;
		i++;
	}
	return (result);
}

int				register_hex(char *str, uint64_t *value, uint64_t default_value)
{
	char		buffer_hex[17];

	if (!str)
	{
		*value = default_value;
		return (1);
	}
	if (!is_hexa(str))
		return (0);
	buffer_hex[16] = 0;
	ft_memset(buffer_hex, '0', 16);
	ft_memcpy(buffer_hex, str, ft_strlen(str) % 17);
	*value = atohex(buffer_hex);
	return (1);
}
