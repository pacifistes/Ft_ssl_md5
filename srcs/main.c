/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 21:23:37 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

# define d datas
static unsigned int reverseHash(unsigned int hash) 
{
	hash = ((hash & 0x000000FF) << 24) |
	((hash & 0x0000FF00) <<  8) |
	((hash & 0x00FF0000) >>  8) |
	((hash & 0xFF000000) >> 24);
  return hash;
}

static void		print_hash(t_hash_info info, char *str, int is_file, char option)
{
	int i;

	i = 0;
	if (str && is_file && !(option & R) && !(option & Q))
		ft_printf("%s (%s) = ", info.type, str);
	if (str && !is_file && !(option & R) && !(option & Q))
		ft_printf("%s (\"%s\") = ", info.type, str);
	while (i < info.size)
	{
		ft_printf("%08x", reverseHash(info.hash[i]));
		i++;
	}
	if (str && is_file && (option & R) && !(option & Q))
		ft_printf(" %s", info.type, str);
	if (str && !is_file && (option & R) && !(option & Q))
		ft_printf(" \"%s\"", info.type, str);
	ft_printf("\n");
	reverseHash(0);
}

static void		execute(t_manager *m)
{
	t_hash_info info;
	t_datas *d;

	if (m->datas == NULL || m->options & P)
	{
		info = hash_fd(m->algo, 0, m->options);
		print_hash(info, NULL, 0, m->options);
	}
	d = m->datas;
	while (d)
	{
		if (d->is_file == 1)
			info = hash_fd(m->algo, open(*d->str, O_RDONLY), m->options);
		else
			info = hash(m->algo, *d->str, m->options);
		print_hash(info, *d->str, d->is_file, m->options);
		d = d->next;
	}
}

int			main(int ac, char **av)
{
	t_manager manager;

	if (!init_manager(&manager, ac, &av))
	{
		ft_printf("Error in parameters, usage: ");
		ft_printf("./ft_ssl sha256|md5 [-pqdr] [-s string ...] [file ...]\n");
		ft_printf("To see description of options :\n ./ft_ssl -h\n");
		return (1);
	}
	execute(&manager);
	while (1);
}

