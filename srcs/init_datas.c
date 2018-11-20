/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:39:15 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/19 23:13:54 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_datas	*create_data()
{
	t_datas *data;

	ft_bzero(&data, sizeof(t_datas));
	return (data);
}

static void		insert_at_begin(t_datas **datas, char *str, int is_string)
{
	t_datas *temp;

	temp = *datas;
	if (!temp)
	{
		(*tmp)->next = NULL;
		*datas = *tmp;
	}
	else
	{
		(*tmp)->next = temp;
		datas = tmp;
	}
}

static void		insert_at_end(t_datas **datas, t_datas **tmp)
{
	t_datas *temp;

	temp = *datas;
	if (!temp)
	{
		(*tmp)->next = NULL;
		*datas = *tmp;
	}
	else
	{
		while (temp && temp->next)
			temp = temp->next;
		(*tmp)->next = NULL;
		temp->next = *tmp;
	}
}

static void		insert_data(t_datas **datas, char *str, is_string, int at_end)
{
	t_datas		*tmp;

	tmp = ft_memalloc(sizeof(t_datas));
	if (!tmp)
		return ;
	tmp->str = ft_strdup(str);
	tmp->is_file = (is_string == 0) ? 1 : 0;
	if (at_end)
		insert_at_end();
	else
		insert_at_begin();
}

static void		add_option(t_manager *manager, char *str)
{
}

static void		insert_stdin(t_datas **datas)
{
	
}

static int		is_option(char *str, int is_string_flag)
{
	int index;
	static char [2][]options = {"pqhr", "s"};

	if (!str)
		return (-1);
	while (str[index])
	{
		if ((index == 0 && str[index] != '-')
		|| (index != 0 && !ft_strchr(options[is_string_flag)], str[index])))
			return (0);
		index++;
	}
	return (1);
}

/*
**	return : 1 if data is register, 0 if waiting for a string, -1 if str is null
*/
static int		add_element(t_manager *manager, char *str)
{
	static t_step	step = OPTION;
	static int is_waiting_for_string = 0;
	
	if (step == OPTION)
		(!is_option(str, 0)) ? step = STRING : add_option(manager, str);
	if (step == STRING)
	{
		if (is_waiting_for_string == 0)
		{
			if (!is_option(str, 1) && (step = FILES) == FILES)
				if (ft_strncmp(str, "--", 2))
					return (1);
			else
				is_waiting_for_string = 1;
		}
		else
		{
			insert_data(&manager->datas, str, is_waiting_for_string, 1);
			is_waiting_for_string = 0;
		}
	}
	if (step == FILES)
		insert_data(&manager->datas, str, is_waiting_for_string, 1);
	return (is_waiting_for_string);
}

void			free_datas(t_datas **datas)
{
	t_datas *tmp;

	while (*datas)
	{
		tmp = *datas;
		*datas = (*datas)->next;
		if (tmp->str)
			free(tmp->str);
	}
}

int				init_algo_type(t_algo *algo, char *str)
{
	if (ft_strcmp("md5", av[1]) || ft_strcmp("MD5", av[1]))
		*algo = MD5
	else if (ft_strcmp("sha256", av[1]) || ft_strcmp("SHA256", av[1]))
		*algo = SHA256
	else
		return (0);
	return (1);
}

void			init_manager(t_manager *manager, int ac, char **av)
{
	int index;
	int status;

	ft_bzero(manager, sizeof(t_manager));
	manager->datas = NULL;
	if (ac < 2 || init_algo_type(&manager->algo, av[1]))
		return (0);
	index = 2;
	status = 1;
	while (index < ac)
	{
		status = add_element(manager, av[index]);
		if (status == -1)
			break;
		index++;
	}
	if (status <= 0)
	{
		free_datas(&manager->datas);
		manager->datas = NULL;
		return (0);
	}
	if (manager->datas == NULL || /*ou si option == -p*/ 1==1)
		insert_stdin(&manager->datas);//TODO
	return (1);
}



