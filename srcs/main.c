/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/05 14:34:23 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		exec_digest_command(t_manager *m)
{
	t_hash_info	info;
	t_datas		*datas;

	if (m->datas == NULL || m->options & P)
	{
		info = hash_fd(m->algo, NULL, m->options);
		print_hash(info, NULL, 0, m->options);
	}
	datas = (t_datas *)m->datas;
	while (datas)
	{
		if (datas->is_file == 1)
			info = hash_fd(m->algo, datas->str, m->options);
		else
			info = hash(m->algo, datas->str, m->options);
		if (!info.error)
			print_hash(info, datas->str, datas->is_file, m->options);
		datas = datas->next;
	}
}

static void		exec_cipher_command(t_manager *m)
{
	(void)m;
}

static void		print_commands(void)
{
	ft_printf("ft_ssl: Error: invalid command.\n");
	ft_printf("Standard commands:\n\n");
	ft_printf("Message Digest commands:\nmd5\nsha256\n\n");
	ft_printf("Cipher commands:\nbase64\ndes\ndes-ecb\ndes-ecb\n");
	ft_printf("des-cbc\n");
}

int				main(int ac, char **av)
{
	static void	(*print[])(void) = {&print_commands,
		&print_message_digest_options,
		&print_cipher_options};
	static void	(*execute[])(t_manager *m) = {&exec_digest_command,
		&exec_cipher_command};
	t_manager	manager;

	if (!init_manager(&manager, ac, av))
	{
		(*print[manager.algo % 3])();
		return (1);
	}
	(*execute[(manager.algo % 3) - 1])(&manager);
	return (0);
}
