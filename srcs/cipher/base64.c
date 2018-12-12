/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:37:26 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/11 19:47:59 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t bitExtracted(uint64_t number, uint64_t nbr_bit, uint64_t pos)
{
	return ((((1 << nbr_bit) - 1) & (number >> pos)));
}

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
			j = bitExtracted(str[i - h], (6 - size), 8 - (6 - size));
		if ((i - h % 4) > 0 && i - h <= lenght)
			j |= bitExtracted(str[i - h - 1], size, 0) << (6 - size);
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
	static char base64_str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

    "0123456789+/";
	int			size;
	int			h;
	int			i;
	int			j;
	char		c;

	if (lenght == 0 || lenght % 4 != 0)
		return NULL;
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
				c = (bitExtracted((ft_strchr(base64_str, str[i]) - base64_str), 6 - size, 0) << (8 - (6 - size)));
				if (str[i + 1] != '=')
					c |= bitExtracted((ft_strchr(base64_str, str[i + 1]) - base64_str),(8 - (6 - size)), 6 - (8 - (6 - size)));
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

void	encode_fd(t_cipher_commands *c)
{
	t_cipher_fd	cipher;
	char		buffer[65];
	int			size;

	cipher.in_fd = (!c->input_file) ? 0 : open(c->input_file, O_RDONLY);
	cipher.out_fd = (!c->output_file) ? 1 : open(c->output_file,O_WRONLY | O_APPEND | O_CREAT | O_TRUNC);
	size = 0;
	ft_bzero(buffer, sizeof(char) * 65);
	while ((cipher.size_buffer = read_fd(cipher.in_fd, cipher.buffer, 48)) > 0)
	{
		size += cipher.size_buffer;
		if (size > 48)
		{
			ft_printf("\n");
			size %= 48;
		}
		encode_block(cipher.buffer, buffer, cipher.size_buffer);			
		ft_putstr_fd(buffer, cipher.out_fd);
		ft_bzero(buffer, sizeof(char) * 65);
	}
	if (cipher.size_buffer == -1)
	{
		ft_printf("Unable to open \'%s\': ", c->input_file);
		ft_printf("No such file or directory");
	}
	if (cipher.out_fd == -1)
		ft_printf("Unable to create \'%s\': Permission denied", c->output_file);
	ft_printf("\n");
}

int			read_fd_without_space(int fd, char *dest, int size)
{
	char		buffer[size];
	int			size_buffer;
	int			ret;
	int			counter;
	int			i;

	size_buffer = 0;
	while (size_buffer < size
	&& (ret = read(fd, buffer, size - size_buffer)) > 0)
	{
		i = 0;
		counter = 0;
		while (i < ret)
		{
			if ((buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\v'
			&& buffer[i] != '\f' && buffer[i] != '\t' && buffer[i] != '\r'))
			{
				dest[size_buffer + counter] = buffer[i];
				counter++;
			}
			i++;
		}
		size_buffer += counter;
	}
	return ((ret == -1) ? ret : size_buffer);
}

void	decode_fd(t_cipher_commands *c)
{
	t_cipher_fd	cipher;
	char		buffer[49];

	cipher.in_fd = (!c->input_file) ? 0 : open(c->input_file, O_RDONLY);
	cipher.out_fd = (!c->output_file) ? 1 : open(c->output_file,
		O_WRONLY | O_APPEND | O_CREAT | O_TRUNC);
	ft_bzero(buffer, sizeof(char) * 49);
	while ((cipher.size_buffer = read_fd_without_space(cipher.in_fd,
	cipher.buffer, 64)) > 0)
	{
		decode_block(cipher.buffer, buffer, cipher.size_buffer);
		if (ft_strlen(buffer) == 0)
			break ;
		else
			ft_putstr_fd(buffer, cipher.out_fd);
		ft_bzero(buffer, sizeof(char) * 49);
	}
	if (cipher.size_buffer == -1)
	{
		ft_printf("Unable to open \'%s\': ", c->input_file);
		ft_printf("No such file or directory");
	}
	if (cipher.out_fd == -1)
		ft_printf("Unable to create \'%s\': Permission denied", c->output_file);
}
