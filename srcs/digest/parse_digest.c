/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_digest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:46:35 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/05 15:16:12 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	add_option(t_manager *manager, char *str)
{
	int index;

	index = 0;
	if (!str)
		return ;
	while (str[index])
	{
		if (index != 0)
		{
			if (str[index] == 'p')
				manager->options |= P;
			else if (str[index] == 'd')
				manager->options |= D;
			else if (str[index] == 'q')
				manager->options |= Q;
			else if (str[index] == 'r')
				manager->options |= R;
			else if (str[index] == 'c')
				manager->options |= C;
		}
		index++;
	}
}

static int	is_option(char *str, int is_string_flag)
{
	int			index;
	static char	*options[] = {"cqpdr", "s"};

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
	{
		if ((index == 0 && str[index] != '-')
		|| (index != 0 && !ft_strchr(options[is_string_flag], str[index])))
			return (0);
		index++;
	}
	return (1);
}

/*
**	return : 1 if data is register, 0 if waiting for a string, -1 if str is null
*/

static int	add_element(t_manager *m, char *str)
{
	static t_step	step = OPTION;
	static int		is_waiting = 0;

	if (step == OPTION)
		(!is_option(str, 0)) ? step = STRING : add_option(m, str);
	if (step == STRING)
	{
		if (is_waiting == 0)
		{
			if (!is_option(str, 1) && (step = FILES) == FILES)
				if (!ft_strcmp(str, "--"))
					return (1);
		}
		else
			insert_data((t_datas **)&m->datas, str, is_waiting, 1);
		is_waiting = (is_waiting == 0 && step == STRING) ? 1 : 0;
	}
	if (step == FILES)
		insert_data((t_datas **)&m->datas, str, is_waiting, 1);
	return ((is_waiting == 0) ? 1 : 0);
}

int			parse_digest(t_manager *m, int ac, char **av)
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
		free_datas((t_datas **)&m->datas);
		m->datas = NULL;
		return (0);
	}
	return (1);
}
