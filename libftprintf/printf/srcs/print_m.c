/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:01:02 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:11:31 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_reverse(char *str)
{
	int		j;
	char	*s1;

	j = -1;
	while (str[++j] != '\0')
		str[j] = (str[j] == '1') ? '0' : '1';
	j = ft_strlen(str);
	s1 = (char*)malloc(sizeof(char) * (j + 1));
	if (!s1)
		return (NULL);
	j--;
	while (str[j] != '0')
	{
		s1[j] = '0';
		j--;
	}
	s1[j] = '1';
	j--;
	while (j >= 0)
	{
		s1[j] = str[j];
		j--;
	}
	return (s1);
}

static void	printnumend(t_flags *fl, t_line *li, long long int *nbr, char **str)
{
	if (fl->min == 1)
	{
		buff_join(*str, &li->b);
		while (fl->field_size > *nbr)
		{
			buff_join(" ", &li->b);
			(*nbr)++;
		}
	}
	else
	{
		while (fl->field_size > *nbr)
		{
			buff_join(" ", &li->b);
			(*nbr)++;
		}
		buff_join(*str, &li->b);
	}
}

static void	printnum_m(t_flags *fl, t_line *li, long long int c)
{
	long long int	nbr[2];
	char			*str;
	char			*tmp;

	li->base = 2;
	li->x = 0;
	nbr[1] = (c < 0) ? 1 : 0;
	if (c < 0)
		c = -c;
	str = ft_itoa_base(c, li->base);
	if (nbr[1] == 1)
		str = ft_free_njoin((char*[]){ft_reverse(str)}, 1, (int[]){1});
	nbr[0] = ft_strlen(str) - 1;
	while (++nbr[0] < 8)
		str = ft_free_njoin((char*[]){"0", str}, 2, (int[]){0, 1});
	if (fl->sharp == 1)
	{
		tmp = str;
		str = (nbr[1] == 1) ? ft_strjoin("1x", str) : ft_strjoin("0x", str);
		nbr[0] = nbr[0] + 2;
		free(tmp);
	}
	printnumend(fl, li, &nbr[0], &str);
	free(str);
}

void		printf_m(va_list ap, t_flags *fl, t_line *li)
{
	long long int c;

	if (fl->type_var1 == 'z')
		c = va_arg(ap, size_t);
	else if (fl->type_var1 == 'j')
		c = va_arg(ap, intmax_t);
	else if (fl->type_var1 == 'l' && fl->type_var2 == '\0')
		c = va_arg(ap, long int);
	else if (fl->type_var1 == 'l' && fl->type_var2 == 'l')
		c = va_arg(ap, long long int);
	else if (fl->type == 'M')
		c = va_arg(ap, long int);
	else
	{
		if (fl->type_var1 == 'h' && fl->type_var2 == '\0')
			c = (short)va_arg(ap, int);
		else if (fl->type_var1 == 'h' && fl->type_var2 == 'h')
			c = (char)va_arg(ap, int);
		else
			c = va_arg(ap, int);
	}
	printnum_m(fl, li, c);
}
