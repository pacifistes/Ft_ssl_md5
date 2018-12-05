/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:59:42 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/05 19:19:30 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		add_input(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->input_file = str;
	return (1);
}

int		add_output(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->output_file = str;
	return (1);
}

int		add_key(t_manager *m, char *str)
{
	(void)m;
	(void)str;
	return (1);
}