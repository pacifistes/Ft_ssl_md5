/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:42:51 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/21 22:24:21 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"
# include <fcntl.h>
# define P (1 << 0)
# define H (1 << 1)
# define Q (1 << 2)
# define R (1 << 3)

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

typedef struct	s_hash_md5_word
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
}				t_hash_md5_word;

typedef struct	s_block
{
	uint32_t	words[16];
}				t_block;

typedef struct	s_datas
{
	char	*str;
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
int				init_manager(t_manager *manager, int ac, char **av);

/*
**	datas_tool.c
*/
void			insert_at_begin(t_datas **datas, t_datas **tmp);
void			insert_at_end(t_datas **datas, t_datas **tmp);
void			insert_data(t_datas **datas, char *str, int is_string,
int at_end);
void			insert_stdin(t_datas **datas);
void			free_datas(t_datas **datas);

/*
**	md5.c
*/
// void			md5(char *str, char options);
// void			md5_fd(int fd, char options);

/*
**	sha256.c
*/
// void			sha256(char *str, char options);
// void			sha256_fd(int fd, char options);

t_hash_md5_word md5_loop(t_block block);

#endif
