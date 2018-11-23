/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:52:13 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:09:09 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include <math.h>
# include "../../libft/includes/libft.h"

typedef	struct	s_flags
{
	char		min;
	char		plus;
	char		zero;
	char		sharp;
	char		space;
	char		type_var1;
	char		type_var2;
	int			field_size;
	int			prec;
	char		type;
}				t_flags;

typedef	struct	s_line
{
	t_buffer	b;
	int			char_write;
	int			base;
	int			x;
	int			prec;
	int			power;
	int			ret;
}				t_line;

typedef	struct	s_num_uox
{
	int nbr;
	int sign;
	int	nbzero;
	int	nbspaces;
}				t_num_uox;

int				ft_printf(const char *format, ...);
char			*ft_convwchar(unsigned int nbr);
int				ft_error(const char **str);
int				search(const char *format);
int				ft_init(va_list ap, const char *format, t_line *li, int i);
void			ft_type_conv(t_flags *fl, va_list ap, t_line *li);
int				init_flags(va_list ap, const char *format, t_flags *fl, int i);
void			printf_char(va_list ap, t_flags *fl, t_line *li);
void			printf_di(va_list ap, t_flags *fl, t_line *li);
void			printf_o(va_list ap, t_flags *fl, t_line *li);
void			printf_p(va_list ap, t_flags *fl, t_line *li);
void			printf_x(va_list ap, t_flags *fl, t_line *li);
void			printf_percent(t_flags *fl, t_line *li);
void			printf_str(va_list ap, t_flags *fl, t_line *li);
void			printf_u(va_list ap, t_flags *fl, t_line *li);
void			printnum_uox(unsigned long long int c, t_flags *fl, t_line *li);
void			printnumber(t_flags *fl, t_line *li, long long int c);
void			printf_b(va_list ap, t_flags *fl, t_line *li);
char			*ft_itoa_base(unsigned long long int value, int base);
void			printf_m(va_list ap, t_flags *fl, t_line *li);
void			printf_f(va_list ap, t_flags *fl, t_line *li);
void			printf_e(va_list ap, t_flags *fl, t_line *li);
void			printf_g(va_list ap, t_flags *fl, t_line *li);
void			printf_void(t_flags *fl, t_line *li);
void			printf_t(va_list ap, t_flags *fl, t_line *li, int nbr);
void			printf_majt(va_list ap, t_flags *fl, t_line *li);
void			printf_w(va_list ap, t_flags *fl, t_line *li);
int				check_type(const char *format, t_flags *fl, int i);
int				search_flag(va_list ap, const char *format, t_flags *fl, int i);
void			print_withnofld(t_flags *f, t_line *l, long long int c, int *n);
void			print_withminbegin(t_flags *fl, t_line *li, long long int c);
void			print_withmin(t_flags *f, t_line *l, long long int c, int *n);
void			printnominbgn(t_flags *f, t_line *l, long long int c, int *n);
void			print_withnomin(t_flags *f, t_line *l, long long int c, int *n);
void			print_numbere(t_flags *fl, t_line *li, long double c);
void			print_numberf(t_flags *fl, t_line *li, long double c);
void			printf_w(va_list ap, t_flags *fl, t_line *li);
void			printf_m(va_list ap, t_flags *fl, t_line *li);
int				countchar(unsigned long long int value, t_line *li);
char			*print_f_prec(t_line *li, int nbr, long double c, char *str);
void			print_fzeprec(t_line *li, int *nbr, long double *c, char **str);
void			begin_e(t_flags *fl, t_line *li, int *nbr, long double *c);
int				ft_wstrlen(unsigned int nbr);
void			printwstring(va_list ap, t_flags *fl, t_line *li);
void			printstring(va_list ap, t_flags *fl, t_line *li);

#endif
