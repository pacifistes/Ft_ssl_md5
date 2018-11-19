/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:50:26 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/13 12:51:23 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_init(va_list ap, const char *format, t_line *li, int i)
{
	t_flags	fl;
	int		j;

	ft_bzero(&fl, sizeof(t_flags));
	j = init_flags(ap, format, &fl, i);
	ft_type_conv(&fl, ap, li);
	return (j);
}
