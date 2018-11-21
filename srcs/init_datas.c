/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:39:15 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/21 18:02:51 by bbrunell         ###   ########.fr       */
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
			else if (str[index] == 'h')
				manager->options |= H;
			else if (str[index] == 'q')
				manager->options |= Q;
			else if (str[index] == 'r')
				manager->options |= R;
		}
		index++;
	}
}

static int	is_option(char *str, int is_string_flag)
{
	int index;
	static char *options[] = {"pqhr", "s"};

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
static int	add_element(t_manager *manager, char *str)
{
	static t_step	step = OPTION;
	static int 		is_waiting_for_string = 0;

	if (step == OPTION)
		(!is_option(str, 0)) ? step = STRING : add_option(manager, str);
	if (step == STRING)
	{
		if (is_waiting_for_string == 0)
		{
			if (!is_option(str, 1) && (step = FILES) == FILES)
				if (!ft_strcmp(str, "--"))
					return (1);
		}
		else
			insert_data(&manager->datas, str, is_waiting_for_string, 1);
		is_waiting_for_string = (is_waiting_for_string == 0 && step == STRING) ? 1 : 0;
	}
	if (step == FILES)
		insert_data(&manager->datas, str, is_waiting_for_string, 1);
	return ((is_waiting_for_string == 0) ? 1 : 0);
}

static int			init_algo_type(t_algo *algo, char *str)
{
	if (!ft_strcmp("md5", str) || !ft_strcmp("MD5", str))
		*algo = MD5;
	else if (!ft_strcmp("sha256", str) || !ft_strcmp("SHA256", str))
		*algo = SHA256;
	else
		return (0);
	return (1);
}

/*
** change 1=1 par 'ou si option == -p'
*/
int			init_manager(t_manager *manager, int ac, char **av)
{
	int index;
	int status;

	ft_bzero(manager, sizeof(t_manager));
	manager->datas = NULL;
	if (ac < 2 || !init_algo_type(&manager->algo, av[1]))
		return (0);
	index = 2;
	status = 1;
	while (index < ac)
	{
		status = add_element(manager, av[index]);
		if (status == -1)
			break ;
		index++;
	}
	if (status <= 0)
	{
		free_datas(&manager->datas);
		manager->datas = NULL;
		return (0);
	}
	return (1);
}
