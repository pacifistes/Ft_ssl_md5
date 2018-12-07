/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:42:51 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/04 18:29:26 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"
# include <fcntl.h>

/*
**	OPTIONS:
**		-p: echo STDIN to STDOUT
**		-h: help
**		-c: to output the digest with separating colons
**		-q: quiet mode
**		-r: reverse the format of the output
**		-d: show blocs bits
*/

# define P (1 << 0)
# define D (1 << 1)
# define Q (1 << 2)
# define R (1 << 3)
# define C (1 << 4)

# define BLOCK_SIZE_CHAR 64

typedef enum	e_step
{
	OPTION,
	STRING,
	FILES
}				t_step;

typedef enum	e_algo
{
	MD5,
	SHA256
}				t_algo;

typedef struct	s_md5_algo
{
	uint32_t	s[64];
	uint32_t	k[64];
	uint32_t	f;
	int			i;
	int			i_block;
}				t_md5_algo;

typedef struct	s_sha256_algo
{
	uint32_t	k[64];
	uint32_t	w[64];
	uint32_t	f;
	uint32_t	g;
	int			i;
	int			i_block;
}				t_sha256_algo;

typedef	struct	s_hash_info
{
	uint32_t	*hash;
	int			size;
	char		*type;
	int			error;
}				t_hash_info;

typedef struct	s_hash
{
	t_hash_info	info;
	int			i;
	int			lenght_str;
	char		str_block[BLOCK_SIZE_CHAR];
	void		(*apply_algo)(uint32_t *block, u_int32_t **hash);
	int			status;
	uint32_t	block[16];
}				t_hash;

typedef struct	s_hash_fd
{
	char		buffer[64];
	int			size_buffer;
	int			ret;
	int			fd;
}				t_hash_fd;

typedef struct	s_datas
{
	char		**str;
	int			is_file;
	void		*next;

}				t_datas;

typedef struct	s_manager
{
	t_datas		*datas;
	char		options;
	t_algo		algo;
}				t_manager;

/*
**	init_datas.c
*/

int				init_manager(t_manager *manager, int ac, char ***av);

/*
**	datas_tool.c
*/

void			insert_at_begin(t_datas **datas, t_datas **tmp);
void			insert_at_end(t_datas **datas, t_datas **tmp);
void			insert_data(t_datas **datas, char **str, int is_string,
int at_end);
void			insert_stdin(t_datas **datas);
void			free_datas(t_datas **datas);

/*
**	create_block.c
*/
void			create_block(t_hash *hash, char options);

/*
**	md5.c
*/

void			init_md5(t_hash *hash);
void			md5(uint32_t *block, u_int32_t **hash);

/*
**	sha256.c
*/

void			init_sha256(t_hash *hash);
void			sha256(uint32_t *block, u_int32_t **hash);

/*
**	sha256_tools.c
*/
uint32_t		rotr(int n, uint32_t x);
uint32_t		sigma0(uint32_t x);
uint32_t		sigma1(uint32_t x);

/*
**	hash.c
*/

t_hash_info		hash_fd(t_algo	algo, char *str, char options);
t_hash_info		hash(t_algo	algo, char *str, char options);

/*
**	print_block.c
*/

void			print_block(t_hash *hash, int nbr_block, int is_one_set);

/*
**	print_hash.c
*/

uint64_t		reverse_u64(uint64_t hash);
uint32_t		reverse_u32(uint32_t hash);
void			print_hash(t_hash_info info, char *str, int is_file,
char options);

#endif
