/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:59:42 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 22:37:18 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		add_input(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->input_file = str;
}

void		add_output(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->output_file = str;
}

void		add_key(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->options.key = str;
}
