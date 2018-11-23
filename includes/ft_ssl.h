/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:42:51 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 22:50:06 by bbrunell         ###   ########.fr       */
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
**		-q: quiet mode
**		-r: reverse the format of the output
**		-d: show blocs bits
*/

# define P (1 << 0)
# define Q (1 << 2)
# define R (1 << 3)
# define D (1 << 1)

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

typedef	struct	s_hash_info
{
	uint32_t	*hash;
	int			size;
	char		*type;
}				t_hash_info;

typedef struct	s_hash
{
	t_hash_info	info;
	int			i;
	int			j;
	char		str_block[BLOCK_SIZE_CHAR];
	void (*apply_algo)(uint32_t *block, u_int32_t **hash);
	int			status;
	uint32_t	*block;
}				t_hash;

typedef struct	s_datas
{
	char	**str;
	int		is_file;
	void	*next;

}				t_datas;

typedef struct	s_manager
{
	t_datas	*datas;
	char	options;
	t_algo	algo;
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

uint32_t *create_block(int *ret, char *str, int lenght_str);
void print_block(uint32_t *block, int lenght);

/*
**	md5.c
*/

void				init_md5(t_hash *hash);
void				md5(uint32_t *block, u_int32_t **hash);

/*
**	sha256.c
*/

void				init_sha256(t_hash *hash);
void				sha256(uint32_t *block, u_int32_t **hash);

/*
**	hash.c
*/

t_hash_info			hash_fd(t_algo	algo, char *str, char options);
t_hash_info			hash(t_algo	algo, char *str, char options);

#endif
