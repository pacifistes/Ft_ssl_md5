/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:24:39 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/21 23:22:44 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <math.h>

t_hash_md5_word md5_loop(t_block block)
{
	t_hash_md5_word words;

	words.a = 0x01234567;
	words.b = 0x89ABCDEF;
	words.c = 0xFEDCBA98;
	words.d = 0x76543210;
	// words.a = 0x67452301;
	// words.b = 0xefcdab89;
	// words.c = 0x98badcfe;
	// words.d = 0x10325476;
	uint32_t s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	uint32_t k[64];

	for (int i = 0; i < 64; i++) {
		k[i] = floor(fabs(sin(i + 1)) * 4294967296);
	}
	int index;
	int block_index;
	uint32_t f;
	t_hash_md5_word new_word;

	new_word.a = words.a;
	new_word.b = words.b;
	new_word.c = words.c;
	new_word.d = words.d;
	index = 0;

	while (index < 64)
	{
		if (index <= 15)
		{
			f = (new_word.b & new_word.c) | ((~new_word.b) & new_word.d);
			block_index = index;
		}
		else if (index <= 31)
		{
			f = (new_word.b & new_word.d) | (new_word.c & (~new_word.d));
			block_index = ((5 * index) + 1) % 16;
		}
		else if (index <= 47)
		{
			f = new_word.b ^ new_word.c ^ new_word.d;
			block_index = ((3 * index) + 5) % 16;
		}
		else
		{
			f = new_word.c ^ (new_word.b | (~new_word.d));
			block_index = (7 * index) % 16;
		}
		// f = f + new_word.a + k[index] + block.words[block_index];
		// new_word.a = new_word.d;
		// new_word.d = new_word.c;
		// new_word.c = new_word.b;
		// new_word.b = new_word.b + ((f << s[index]) | (f >> (32-s[index])));
		uint32_t temp = new_word.d;
        new_word.d = new_word.c;
        new_word.c = new_word.b;
        new_word.b = (new_word.a + f + k[index] + block.words[block_index]) + ((f << s[index]) | (f >> (32-s[index]))) + new_word.b;
        new_word.a = temp;
		index++;
	}

	new_word.a += words.a;
	new_word.b += words.b;
	new_word.c += words.c;
	new_word.d += words.d;
	return new_word;
}

// void md5(char *str, char options)
// {
// 	t_hash_md5_word words;
// 	t_block block;
// 	int index;

// 	words.a = 0x67452301;
// 	words.b = 0xefcdab89;
// 	words.c = 0x98badcfe;
// 	words.d = 0x10325476;
// 	index = 0;
// 	while (str[index])
// 	{
// 		block = create_block(str, &index);
// 		words = md5_loop(words, block);
// 	}
// }

// void print_md5(t_hash_md5_word word, char *str)
// {

// }

// void md5(t_manager *manager)
// {
// 	(void) manager;
// 	// t_hash_md5_word words;

// 	// words.a = 0x67452301;
// 	// words.b = 0xefcdab89;
// 	// words.c = 0x98badcfe;
// 	// words.d = 0x10325476;
	
// 	// while (manager->str[index])
// 	// {
// 	// 	block = create_block(manager->str, &index);
// 	// 	words = md5_loop(words, block);
// 	// }
// }

// t_hash_md5_word		md5_fd(int fd)
// {
// 	t_block block;
// 	t_hash_md5_word words;
// 	char *buffer;
// 	int number_of_block;
// 	int ret;

// 	number_of_block = 0;
// 	while ((ret = read(fd, buffer, 64)) >= 0)
// 	{
// 		if (ret == 64)
// 		{
// 			//remplir le block
// 		}
// 		else
// 		{

// 		}
// 	}
// 	return words;
// }

// t_hash_md5_word		md5_non_fd(char *str)
// {
// 	t_block block;
// 	int index;

// 	index = 0;
// }


// int			get_lines(int const fd, char **lines)
// {
// 	int			ret;
// 	char		*buffer;
// 	char		*tmp;

// 	if (fd < 0 || !lines)
// 		return (-1);
// 	*lines = ft_strnew(0);
// 	buffer = ft_strnew(BUFF_SIZE);
// 	while ((ret = read(fd, buffer, BUFF_SIZE)) >= 0)
// 	{
// 		if (ret == 0)
// 		{
// 			if (buffer)
// 				ft_strdel(&buffer);
// 			return (0);
// 		}
// 		tmp = buffer;
// 		*lines = ft_strjoin(*lines, buffer);
// 		ft_strdel(&tmp);
// 		buffer = ft_strnew(BUFF_SIZE);
// 	}
// 	ft_strdel(lines);
// 	return (-1);
// }
