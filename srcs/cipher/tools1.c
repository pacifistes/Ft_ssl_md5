/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:59:48 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/12 22:03:01 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		add_password(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->options.password = str;
}

void		add_salt(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->options.salt = str;
}

void		add_vector(t_manager *m, char *str)
{
	((t_cipher_commands*)m->datas)->options.vector = str;
}
