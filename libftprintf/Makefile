NAME = libftprintf.a

SRCSPATH = srcs/

LIBPATH = libft/

PRINTFPATH = printf/

INCLUPATH = includes/

SRCS_LIBFT = ft_strjoin.c ft_strlen.c ft_strnew.c ft_strsub.c ft_atoi.c \
		ft_strcmp.c ft_putstr.c ft_putchar.c ft_putstr_fd.c ft_verifint.c \
		ft_putnbr.c ft_strsplit.c ft_strdel.c get_next_line.c ft_check_end.c \
		ft_memalloc.c ft_strdup.c ft_bzero.c ft_strstr.c ft_putendl.c \
		ft_itoll.c ft_free_join.c ft_free_join_char.c  ft_strlen_char.c \
		free_tab_str.c ft_free1_join_char.c ft_free_njoin.c buff_join.c \
		buff_join_nstr.c ft_strncmp.c size_long_long.c print_nchar.c \
		ft_putendl_fd.c  buff_sub_join.c buff_join_char.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strtrim.c\
		ft_strstr.c\
		ft_strsplit.c\
		ft_strrev.c\
		ft_strrchr.c\
		ft_strnstr.c\
		ft_strnequ.c\
		ft_strncat.c\
		ft_strmapi.c\
		ft_strmap.c\
		ft_strlcat.c\
		ft_striteri.c\
		ft_striter.c\
		ft_strequ.c\
		ft_strcpy.c\
		ft_strncpy.c\
		ft_strclr.c\
		ft_strchr.c\
		ft_strcat.c\
		ft_range.c\
		ft_putnbr_fd.c\
		ft_putchar_fd.c\
		ft_print_bits.c\
		ft_memset.c\
		ft_memmove.c\
		ft_memdel.c\
		ft_memcpy.c\
		ft_memcmp.c\
		ft_memchr.c\
		ft_memccpy.c\
		ft_lstnew.c\
		ft_lstmap.c\
		ft_lstiter.c\
		ft_lstdelone.c\
		ft_lstdel.c\
		ft_lstadd.c\
		ft_itoa.c\
		ft_iterative_power.c\
		ft_isprint.c\
		ft_isdigit.c\
		ft_isascii.c\
		ft_isalpha.c\
		ft_isalnum.c\
		ft_islower.c\
		ft_is_negative.c\
		buff_free_njoin.c\
		ft_print_tab.c\
		ft_strtabdup.c \
		ft_itoa_base.c \
		base_len.c

SRCS_PRINTF = 	begin_e.c          ft_printf.c        print_numbere.c    print_w.c\
check_type.c       ft_type_conv.c     print_numberf.c    print_wstring.c\
ft_bzero.c         init_flags.c       print_numberf2.c   printnum_uox.c\
ft_convwchar.c     print_char.c       print_other.c      printnumwithflag.c\
ft_error.c         print_di.c         print_percent.c    search.c\
ft_init.c          print_efg.c        print_string.c     search_flag.c\
print_m.c          print_uox.c\

SRC = 	$(addprefix $(addprefix $(LIBPATH), $(SRCSPATH)), $(SRCS_LIBFT))\
		$(addprefix $(addprefix $(PRINTFPATH), $(SRCSPATH)), $(SRCS_PRINTF))\

WFLAGS = -Wall -Werror -Wextra

CC = gcc -g

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) -c -I $(addprefix $(LIBPATH), $(INCLUPATH)) -I $(addprefix $(PRINTFPATH), $(INCLUPATH)) $< -o $@

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
