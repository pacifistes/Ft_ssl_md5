/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:42:51 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/19 22:45:11 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"

typedef enum		e_step
{
	OPTION,
	STRING,
	FILE
}					t_step;

typedef enum		e_plop
{
	MD5,
	SHA256,
	OTHER
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
	char	*mode;
}					t_manager;

static struct		s_tab_to_function
{
	char	**str;
	int		*index;
}					t_tab_to_function;

int				init_manager(t_manager *manager, int ac, char **av);
#endif
