/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:37:26 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/16 19:44:38 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	encode_block(char *str, char *buffer, int lenght)
{
	int		i;
	int		j;
	int		h;
	int		size;

	if (lenght < 1 || lenght > 48)
		return ;
	size = 0;
	i = -1;
	h = 0;
	while (++i < (((lenght - 1) / 3) + 1) * 4 && (j = 0) == 0)
	{
		size = (i % 4 == 0) ? 0 : 8 - (6 - size);
		h = (i != 0 && i % 4 == 0) ? h + 1 : h;
		if (i - h < lenght)
			j = bit_extractor(str[i - h], (6 - size), 8 - (6 - size));
		if ((i - h % 4) > 0 && i - h <= lenght)
			j |= bit_extractor(str[i - h - 1], size, 0) << (6 - size);
		else if (i - h > lenght)
			j = -1;
		buffer[i] = (j < 0) * 61 + (j >= 0) * (j + ('A'
		+ (j > 25) * ('a' - 'Z' - 1) - (j > 51) * ('z' - '0' + 1)
		- (j > 61) * ('9' - '+' + 1) + (j > 62) * ('/' - '+' - 1)));
	}
}

char		*decode_block(char *str, char *buffer, int lenght)
{
	static int	terminator = 0;
	static char base64_str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrst"

	"uvwxyz0123456789+/";
	int			size;
	int			h;
	int			i;
	int			j;
	char		c;

	if (lenght == 0 || lenght % 4 != 0)
		return (NULL);
	size = 0;
	i = -1;
	h = 0;
	while (++i < lenght && (j = 0) == 0)
	{
		h = (i != 0 && i % 4 == 0) ? h + 1 : h;
		size = (i % 4 == 0) ? 0 : 8 - (6 - size);
		if (str[i] == '=')
		{
			buffer[i] = 0;
			terminator = 1;
		}
		else if (!terminator)
		{
			if (!terminator && ft_strchr(base64_str, str[i]) && (ft_strchr(base64_str, str[i + 1]) || str[i + 1] == '='))
			{
				c = (bit_extractor((ft_strchr(base64_str, str[i]) - base64_str), 6 - size, 0) << (8 - (6 - size)));
				if (str[i + 1] != '=')
					c |= bit_extractor((ft_strchr(base64_str, str[i + 1]) - base64_str), (8 - (6 - size)), 6 - (8 - (6 - size)));
				buffer[i - h] = c;
			}
			else
				return (NULL);
		}
		else
			return (NULL);
	}
	return (buffer);
}

void	base64_encode(t_cipher_fd *cipher)
{
	char	buffer[65];
	int		size;

	size = 0;
	ft_bzero(buffer, sizeof(char) * 65);
	while ((cipher->size_buffer = read_fd(cipher->in_fd, cipher->buffer, 48))
	> 0)
	{
		size += cipher->size_buffer;
		if (size > 48)
		{
			ft_putendl_fd("\n", cipher->out_fd);
			size %= 48;
		}
		encode_block(cipher->buffer, buffer, cipher->size_buffer);
		ft_putstr_fd(buffer, cipher->out_fd);
		ft_bzero(buffer, sizeof(char) * 65);
	}
	ft_putendl_fd(buffer, cipher->out_fd);
}

void	base64_decode(t_cipher_fd *cipher)
{
	char	buffer[49];

	ft_bzero(buffer, sizeof(char) * 49);
	while ((cipher->size_buffer = read_fd_without_space(cipher->in_fd,
	cipher->buffer, 64)) > 0)
	{
		decode_block(cipher->buffer, buffer, cipher->size_buffer);
		if (ft_strlen(buffer) == 0)
			break ;
		else
			ft_putstr_fd(buffer, cipher->out_fd);
		ft_bzero(buffer, sizeof(char) * 49);
	}
}

void	base64(t_cipher_fd *cipher, int is_decode)
{
	static void (*apply_algo[])(t_cipher_fd *) = {
		&base64_encode,
		&base64_decode
	};

	(*apply_algo[is_decode])(cipher);
}
