/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cipher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:46:51 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/05 19:18:46 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	option_value(char c)
{
	if (c == 'a')
		return (A);
	else if (c == 'd')
		return (D);
	else if (c == 'e')
		return (E);
	else if (c == 'i')
		return (I);
	else if (c == 'k')
		return (K);
	else if (c == 'o')
		return (K);
	else if (c == 'p')
		return (P);
	else if (c == 'P')
		return (MAJ_P);
	else if (c == 's')
		return (S);
	else if (c == 'v')
		return (V);
	return (0);
}

static int	is_option(t_manager *m, char *str, int is_waiting)
{
	int			index;
	char		c;
	static char	*options[] = {"deio", "adeikopsvP"};

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
	{
		c = str[index];
		if ((index == 0 && c != '-') || (index != 0 &&
		!ft_strchr(options[((m->algo / 3) == 0) ? 0 : 1], c)))
			return (0);
		m->options |= option_value(c);
		if (!is_waiting && ft_strchr("ikopsv", c))
			is_waiting = option_value(c);
		index++;
	}
	return (is_waiting);
}

static int insert_element(t_manager *m, char *str, int is_waiting)
{
	static int options[] = {I, O, K, P, S, V};
	static int (*add[])(t_manager *, char *) = {&add_input, &add_output,
	&add_key, &add_password, &add_salt, &add_vector};
	int i;

	i = -1;
	while (++i < 6)
		if (is_waiting & options[i])
			return ((*add[i])(m, str));
	return (0);
}

static int	add_element(t_manager *m, char *str)
{
	static int		is_waiting = 0;

	if (!is_waiting && !(is_waiting = is_option(m, str, is_waiting)))
		(void)is_waiting;
	else
		return (insert_element(m, str, is_waiting));
	return ((is_waiting == 0) ? 1 : 0);
}

int			parse_cipher(t_manager *m, int ac, char **av)
{
	int index;
	int status;

	index = 2;
	status = 1;
	while (index < ac)
	{
		status = add_element(m, av[index]);
		if (status == -1)
			break ;
		index++;
	}
	if (status <= 0)
	{
		// FREE DATAS
		// free_datas((t_datas **)&m->datas);
		m->datas = NULL;
		return (0);
	}
	return (1);
}
