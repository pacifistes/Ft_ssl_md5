/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/30 15:57:54 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		print_options(void)
{
	ft_printf("options are\n");
	ft_printf("%-4s to output the digest with separating colons\n", "-c");
	ft_printf("%-4s to display blocs's info\n", "-d");
	ft_printf("%-4s echo STDIN to STDOUT and append the checksum", "-p");
	ft_printf(" to STDOUT\n");
	ft_printf("%-4s quiet mode\n", "-q");
	ft_printf("%-4s reverse the format of the output\n", "-r");
	ft_printf("%-4s print the sum of the given string\n", "-s");
}

static void		execute(t_manager *m)
{
	t_hash_info	info;
	t_datas		*datas;

	if (m->datas == NULL || m->options & P)
	{
		info = hash_fd(m->algo, NULL, m->options);
		print_hash(info, NULL, 0, m->options);
	}
	datas = m->datas;
	while (datas)
	{
		if (datas->is_file == 1)
			info = hash_fd(m->algo, *datas->str, m->options);
		else
			info = hash(m->algo, *datas->str, m->options);
		print_hash(info, *datas->str, datas->is_file, m->options);
		datas = datas->next;
	}
}

int				main(int ac, char **av)
{
	t_manager manager;

	if (!init_manager(&manager, ac, &av))
	{
		if (ac >= 2 && !ft_strcmp("-h", av[1]))
			print_options();
		else
		{
			ft_printf("Error in parameters, usage: ./ft_ssl ");
			ft_printf("sha256|md5 [-pcqdr] [-s string ...] [file ...]\n");
			ft_printf("To see description of options :\n ./ft_ssl -h\n");
		}
		return (1);
	}
	execute(&manager);
	(void)ac;
	(void)av;

	ft_printf("verif = [%s]\n", encode_block("abc", 3));
	return (0);
}
