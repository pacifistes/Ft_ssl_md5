/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/20 17:43:41 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		md5(t_manager *manager)
{
	t_datas *datas;

	datas = manager->datas;
	if (datas == NULL || GET(manager->options, P))
	{
		ft_printf("je passe dans l'option p\n");
		//READ STDIN
	}
	while (datas)
	{
		datas = datas->next;
	}
}

void		sh256(t_manager *manager)
{
	(void)manager;
}

int			main(int ac, char **av)
{
	t_manager manager;
	if (!init_manager(&manager, ac, av))
	{
		ft_printf("Error in parameters, usage: ");
		ft_printf("./ft_ssl sha256|md5 [-pqhr] [-s string ...] [file ...]");
		return (1);
	}
	if (manager.algo ==  MD5)
		md5(&manager);
	else
		sh256(&manager);
	ft_printf("char = %d byte\n", sizeof(char));
	ft_printf("short = %d byte\n", sizeof(short));
	ft_printf("int = %d byte\n", sizeof(int));
	ft_printf("long = %d byte\n", sizeof(long));
	ft_printf("long long = %d byte\n", sizeof(long long));
	// t_datas *datas;
	// datas = manager.datas;
	// ft_printf("%b\n", manager.options);
	// while (datas)
	// {
	// 	if (datas->is_file)
	// 		ft_printf("{%s} is a file\n", datas->str);
	// 	else
	// 		ft_printf("{%s} is string\n", datas->str);
	// 	datas = datas->next;
	// }
	return (0);
}
