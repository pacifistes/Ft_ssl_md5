/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:39:15 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 18:55:19 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	init_algo_type(t_algo *algo, char *str)
{
	if (!ft_strcmp("md5", str) || !ft_strcmp("MD5", str))
		*algo = MD5;
	else if (!ft_strcmp("sha256", str) || !ft_strcmp("SHA256", str))
		*algo = SHA256;
	else if (!ft_strcmp("base64", str) || !ft_strcmp("BASE64", str))
		*algo = BASE_64;
	else if (!ft_strcmp("des", str) || !ft_strcmp("DES", str)
	|| !ft_strcmp("des-cbc", str) || !ft_strcmp("DES-CBC", str))
		*algo = DES_CBC;
	else if (!ft_strcmp("des-ecb", str) || !ft_strcmp("DES-ECB", str))
		*algo = DES_ECB;
	else if (!ft_strcmp("des-cfb", str) || !ft_strcmp("DES-CFB", str))
		*algo = DES_CFB;
	else if (!ft_strcmp("des-ofb", str) || !ft_strcmp("DES-OFB", str))
		*algo = DES_OFB;
	else if (!ft_strcmp("des-ctr", str) || !ft_strcmp("DES-CTR", str))
		*algo = DES_CTR;
	else if (!ft_strcmp("des-pcbc", str) || !ft_strcmp("DES-PCBC", str))
		*algo = DES_PCBC;
	else
	{
		*algo = NONE;
		return (0);
	}
	return (1);
}

int			init_manager(t_manager *m, int ac, char **av)
{
	int			status;
	static int	(*parse[])(t_manager *, int, char **) = {&parse_digest,
		&parse_cipher};

	ft_bzero(m, sizeof(t_manager));
	if (ac < 2 || !init_algo_type(&m->algo, av[1]))
		return (0);
	if ((status = (*parse[base_len(m->algo, 10) - 1])(m, ac, av)) <= 0)
		return (0);
	return (1);
}
