/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cipher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:46:51 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 15:48:24 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	option_value(char c)
{
	static char	*str = "pdqrceioaksvPl";
	int			i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1 << i);
		i++;
	}
	return (0);
}

static int	is_option(t_manager *m, char *str, int is_waiting)
{
	static char	*options[] = {"deio", "adeikopsvlP"};
	int			i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if ((i == 0 && str[i] != '-') || (i != 0 &&
		!ft_strchr(options[(m->algo == BASE_64) ? 0 : 1], str[i])))
			return (-1);
		m->options |= option_value(str[i]);
		if (m->options & D && str[i] == 'e')
			m->options &= (~D);
		else if (m->options & E && str[i] == 'd')
			m->options &= (~E);
		if (!is_waiting && ft_strchr("ikopsv", str[i]))
			is_waiting = option_value(str[i]);
		i++;
	}
	return (is_waiting);
}

static void	insert_element(t_manager *m, char *str, int is_waiting)
{
	static int	options[] = {I, O, K, P, S, V};
	static void	(*add[])(t_manager *, char *) = {&add_input, &add_output,
	&add_key, &add_password, &add_salt, &add_vector};
	int			i;

	i = -1;
	while (++i < 6)
		if (is_waiting & options[i])
			(*add[i])(m, str);
}

static int	add_element(t_manager *m, char *str)
{
	static int		is_waiting = 0;

	if (is_waiting)
	{
		insert_element(m, str, is_waiting);
		is_waiting = 0;
		return (1);
	}
	if (!is_waiting && (is_waiting = is_option(m, str, is_waiting)) == -1)
		return (-1);
	if (!is_waiting || is_waiting & I || is_waiting & O)
		return (1);
	return (0);
}

int			parse_cipher(t_manager *m, int ac, char **av)
{
	int	index;
	int	status;

	m->datas = (t_cipher_commands *)ft_memalloc(sizeof(t_cipher_commands));
	ft_bzero(m->datas, sizeof(t_cipher_commands));
	m->options |= E;
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
		free(m->datas);
		m->datas = NULL;
		return (0);
	}
	return (1);
}
