/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 16:36:42 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		open_all_fd(t_cipher_commands *c, t_cipher_fd *cipher)
{
	struct stat stat;

	if ((cipher->in_fd = (!c->input_file) ? 0
	: open(c->input_file, O_RDONLY)) < 0 || fstat(cipher->in_fd, &stat) == -1)
	{
		ft_printf("Unable to open \'%s\': ", c->input_file);
		ft_printf("No such file or file.");
	}
	else if (S_ISDIR(stat.st_mode))
		ft_printf("It's a directory. Try again\n");
	else if (!(stat.st_mode & S_IRUSR))
		ft_printf("the file is not readdable\n");
	else
	{
		cipher->out_fd = (!c->output_file) ? 1 : open(c->output_file, O_WRONLY
		| O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
		if (cipher->out_fd < 0)
			ft_printf("the file \'%s\' is not writtable\n", c->output_file);
		else
			return (1);
	}
	return (0);
}

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
	t_cipher_commands	*c;
	t_cipher_fd			cipher;

	c = (t_cipher_commands*)m->datas;
	ft_bzero(&cipher, sizeof(t_cipher_fd));
	if (!open_all_fd(c, &cipher))
		return ;
	if (m->algo == BASE_64)
		base64(&cipher, m->options & D);
	else
		des(c, &cipher, m->options, m->algo);
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
	static void	(*print[])(void) = {
		&print_commands,
		&print_message_digest_options,
		&print_cipher_options
	};
	static void	(*execute[])(t_manager *m) = {
		&exec_digest_command,
		&exec_cipher_command
	};
	t_manager	manager;

	srand(time(NULL));
	if (!init_manager(&manager, ac, av))
	{
		(*print[(manager.algo == 0) ? 0 : base_len(manager.algo, 10)])();
		return (1);
	}
	(*execute[base_len(manager.algo, 10) - 1])(&manager);
	return (0);
}
