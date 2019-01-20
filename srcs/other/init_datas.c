/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:39:15 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/20 13:42:25 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	init_algo_type(t_algo *algo, char *str)
{
	static char		*algos_str[] = {"md5", "sha256", "base64", "des", "des-cbc",
						"des-ecb", "des-cfb", "des-ofb", "des-ctr", "des-pcbc"};
	static t_algo	algos_enum[] = {MD5, SHA256, BASE_64, DES_CBC, DES_CBC,
								DES_ECB, DES_CFB, DES_OFB, DES_CTR, DES_PCBC};
	int				i;

	*algo = NONE;
	i = 0;
	while (i < 10)
	{
		if (!ft_strcmp(str, algos_str[i]))
		{
			*algo = algos_enum[i];
			return (1);
		}
		i++;
	}
	return (0);
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
