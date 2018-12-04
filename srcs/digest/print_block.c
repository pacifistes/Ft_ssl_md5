/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:25:52 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/26 19:24:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_message_line(t_hash *hash, int i)
{
	i = i * 4;
	if (ft_isprint(hash->str_block[i + 3]))
		ft_printf("|%8c ", hash->str_block[i + 3]);
	else
		ft_printf("|(%6d) ", hash->str_block[i + 3]);
	if (ft_isprint(hash->str_block[i + 2]))
		ft_printf("%8c ", hash->str_block[i + 2]);
	else
		ft_printf("(%6d) ", hash->str_block[i + 2]);
	if (ft_isprint(hash->str_block[i + 1]))
		ft_printf("%8c ", hash->str_block[i + 1]);
	else
		ft_printf("(%6d) ", hash->str_block[i + 1]);
	if (ft_isprint(hash->str_block[i]))
		ft_printf("%8c|\n", hash->str_block[i]);
	else
		ft_printf("(%6d)|\n", hash->str_block[i]);
}

static void	print_end_of_message(t_hash *hash, int i)
{
	int j;

	j = -1;
	ft_printf("|");
	while (++j < 3 - (hash->lenght_str % 4))
		ft_printf((j == 0) ? "%8s" : " %8s", "padding");
	ft_printf((j == 0) ? "%8s" : " %8s", "add 1");
	while (++j < 4)
	{
		if (ft_isprint(hash->str_block[i * 4 + 3 - j]))
		{
			ft_printf((j == 0) ? "%8c" : " %8c",
			hash->str_block[i * 4 + 3 - j]);
		}
		else
		{
			ft_printf((j == 0) ? "(%6d)" : " (%6d)",
			hash->str_block[i * 4 + 3 - j]);
		}
	}
	ft_printf("|\n");
}

static void	print_padding_or_size(int is_one_set, int i)
{
	if (is_one_set && i >= 14)
		ft_printf("|                SIZE               |\n");
	else
	{
		ft_printf("|%8s %8s %8s %8s|\n", "padding", "padding",
		"padding", "padding");
	}
}

void		print_block(t_hash *hash, int nbr_block, int is_one_set)
{
	int nbr_delimiter;
	int i;

	nbr_delimiter = (38 - (7 + base_len(nbr_block, 10))) / 2;
	ft_printf("%.*s", nbr_delimiter, "=====================");
	ft_printf(" BLOCK %d ", nbr_block);
	ft_printf("%.*s\n", nbr_delimiter, "=====================");
	i = -1;
	while (++i < 16)
	{
		if (i < hash->lenght_str / 4)
			print_message_line(hash, i);
		else
		{
			(!is_one_set) ? print_end_of_message(hash, i)
			: print_padding_or_size(is_one_set, i);
			is_one_set = 1;
		}
		ft_printf("|%h08b", ((hash->block[i] & 0xFF000000) >> 24));
		ft_printf(" %h08b", ((hash->block[i] & 0x00FF0000) >> 16));
		ft_printf(" %h08b", ((hash->block[i] & 0x0000FF00) >> 8));
		ft_printf(" %h08b|\n", ((hash->block[i] & 0x000000FF)));
	}
	ft_printf("=====================================\n\n");
}
