/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/21 22:25:51 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// t_blocks	create_block(char *str, int *index)
// {
// 	t_blocks		tmp;
// 	int i;
// 	int j;
// 	if (!tmp)
// 		return ;
// 	insert_at_end(datas, &tmp);
// }

// void		execute(t_manager *manager)
// {
// 	if (manager->datas == NULL || manager->options & P)
// 	{
// 		if (manager->algo == MD5)
// 			md5_fd(0, manager->options);
// 		else
// 			sha256_fd(0, manager->options);
// 	}
// 	while (manager->datas)
// 	{
// 		if (manager->algo == MD5)
// 		{
// 			if (manager->datas->is_file == 1)
// 				md5_fd(open(manager->datas->str, O_RDONLY), manager->options);
// 			else
// 				md5(manager->datas->str, manager->options);
// 		}
// 		else
// 		{
// 			if (manager->datas->is_file == 1)
// 				sha256_fd(open(manager->datas->str, O_RDONLY), manager->options);
// 			else
// 				sha256(manager->datas->str, manager->options);
// 		}
// 		manager->datas = manager->datas->next;
// 	}
// }


# define SIZE_BUF 64

static void             print_last_memory_hex(size_t len, size_t size, size_t size2,
						unsigned char *str)
{
		int i;

		i = len;
		while (i--)
				ft_printf("   ");
		while (size2 < size)
		{
				ft_printf("%c", ((ft_isprint(str[size2])) ? str[size2] : '.'));
				size2++;
		}
		i = len;
		while (i--)
				ft_printf(" ");
		ft_printf("|");
}

void                    print_memory_hex(void *data, size_t blk_size)
{
		size_t            size;
		size_t            size2;
		unsigned char    *str;

		str = data;
		size = 0;
		size2 = 0;
		ft_printf("\n|\t");
		while (size < blk_size)
		{
				ft_printf("%08b ", str[size]);
				if (++size % 4 == 0)
				{
						while (size2 < size)
						{
								ft_printf("%c", ((ft_isprint(str[size2])) ? str[size2] : '.'));
								size2++;
						}
						if (size2 < blk_size)
								ft_printf("|\n|\t");
				}
		}
		print_last_memory_hex(size - size2, size, size2, str);
		ft_printf("\n");
}

void algo(uint32_t *msg, uint32_t opts)
{
    uint32_t s[64] = {7, 12, 17, 22,  7, 12, 17, 22, 7, 12, 17, 22,
    7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
    14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11,
    16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    uint32_t i;
    uint32_t f;
    uint32_t g;
    uint32_t h[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    uint32_t k[64] ={
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

    (void)k;
    (void)h;
    (void)opts;
    uint32_t a = h[0];
    uint32_t b = h[1];
    uint32_t c = h[2];
    uint32_t d = h[3];

    i = 0;
    // print_memory_hex(msg, SIZE_BUF);
    while (i < 64)
    {
        if (i <= 15)
        {
            f = (b & c) | (~b & d);// ft_f(b, c, d); //(b et c)ou((non b)et d)
            g = i;
        }
        else if (i <= 31)
        {
            f = (b & d) | (c & ~d) ;//ft_g(b, c, d); //d et b)ou((non d)et c)
            g = (5 * i + 1) % 16;
        }
        else if (i <= 47)
        {
            f = b ^ c ^ d;//ft_h(b, c, d); //b xor c xor d
            g = (3 * i + 5) % 16;
        }
        else if (i <= 63)
        {
            f = (c ^ (b | ~d)) ;//ft_i(b, c, d); //c xor (b ou(non d))
            g = (7 * i) % 16;
        }
        f = f + a + k[i] + msg[g];
        a = d;
        d = c;
        c = b;
        b += (f << s[i]) | (f >> (32 - s[i]));
        i++;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;


    // uint32_t w = 256;

    ft_printf("~~~~~~~~~~~~~~~~~\n");
    // print_memory_hex((void *)&w, sizeof(uint32_t));

    ft_printf("~~~~~~~~~~~~~~~~~\n");
    ft_printf("MD5(vide)= %x%x%x%x\n", h[0], h[1], h[2], h[3]);
    ft_printf("MD5(vide)= %x%x%x%x\n", h[3], h[2], h[1], h[0]);
    // ft_printf("MD5(vide)= %08x%08x%08x%08x\n", h[3], h[2], h[1], h[0]);
    ft_printf("~~~~~~~~~~~~~~~~~\n");
}

int			main(int ac, char **av)
{
	int i;
	// t_manager manager;
	// if (!init_manager(&manager, ac, av))
	// {
	// 	ft_printf("Error in parameters, usage: ");
	// 	ft_printf("./ft_ssl sha256|md5 [-pqhr] [-s string ...] [file ...]");
	// 	return (1);
	// }
	// execute(&manager);


	(void)ac;
	(void)av;
	i = 0;
	t_block block;
	int j;
	uint32_t plop[16];
	while (i < 16)
	{
		j = 0;
		block.words[i] = 0;
		plop[i] = 0;
		while (j < 32)
		{
			block.words[i] |= 0 << j;
			j++;
		}
		if (i == 0)
		{
		}
		// ft_printf("%x\n", block.words[i]);
		print_memory_hex(&block.words[i], sizeof(u_int32_t));
		i++;
	}
	// block.words[0] = 1;
	// block.words[15] |= 1 << 0;

	// ft_printf("%x\n", words.a);
	i = 0;
		t_hash_md5_word words;
	while (i < 32)
	{
		block.words[0] |= (1 << i);
		words = md5_loop(block);
		plop[0] |= (1 << i);
		algo(plop, 10);
		block.words[0] &= ~(1 << i);
		plop[0] &= ~(1 << i);
		ft_printf("le miens :%x%x%x%x\n", words.a, words.b, words.c, words.d);
		i++;
	}

	// t_datas *datas;
	// datas = manager.datas;
	// ft_printf("%b\n", manager.options);
	// while (datas)
	// {
	// 	if (datas->is_file)
	// 		ft_printf("{%s} is a file\n", datas->str);
	// 	else
	// 		ft_printf("{%s} is string\n", datas->str);
	// 	datas = datas->next;
	// }
	return (0);
}

