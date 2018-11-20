/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/19 22:44:41 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			main(int ac, char **av)
{
	t_manager manager;

	if (!init_manager(&manager, ac, av))
		ft_printf("usage: ./ft_ssl sha256|md5 [-pqhr] [-s string ...] [file ...]");
	return (0);
}
