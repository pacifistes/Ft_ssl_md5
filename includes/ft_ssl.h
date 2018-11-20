/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:42:51 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/20 17:43:06 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"

# define P 0
# define H 1
# define Q 2
# define R 3
# define GET(value, bit) (value >> bit) & 1
# define SET(value, bit) value |= (1 << bit)
# define CLEAR(value, bit) value & ~(1 << bit)

typedef enum		e_step
{
	OPTION,
	STRING,
	FILES
}					t_step;

typedef enum		e_algo
{
	MD5,
	SHA256
}					t_algo;

typedef struct		s_datas
{
	char	*str;
	int		is_file;
	void	*next;

}					t_datas;

typedef struct		s_manager
{
	t_datas	*datas;
	char	options;
	t_algo	algo;
}					t_manager;



int				init_manager(t_manager *manager, int ac, char **av);
void			insert_at_begin(t_datas **datas, t_datas **tmp);
void			insert_at_end(t_datas **datas, t_datas **tmp);
void			insert_data(t_datas **datas, char *str, int is_string,
int at_end);
void			insert_stdin(t_datas **datas);
void			free_datas(t_datas **datas);
#endif
