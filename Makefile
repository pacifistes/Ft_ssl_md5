NAME = ft_ssl

SRCSPATH = srcs/
INCLUDES = includes/
LIBFT = libftprintf/
LIBFTINCL = libftprintf/printf/includes/

SRCS = main.c \
	init_datas.c \
	datas_tools.c \
	md5.c \
	sha256.c

SRC = $(addprefix $(SRCSPATH), $(SRCS))

WFLAGS = -Wall -Werror -Wextra -march=native

CC = gcc -g

OBJ = $(SRC:.c=.o)

all : $(NAME)


libftprintf/libftprintf.a: libftprintf/libft/srcs/ libftprintf/libft/includes/ libftprintf/printf/ libftprintf/libft/includes/ libftprintf/Makefile
	make -C $(LIBFT) all

%.o: %.c
	$(CC) -g -c $(WFLAGS) -I $(LIBFTINCL) -I $(INCLUDES) $< -o $@

$(NAME) : libftprintf/libftprintf.a $(OBJ)
	$(CC) -g -o $(NAME) $(OBJ) $(WFLAGS) -I $(LIBFTINCL) -I $(INCLUDES) -L $(LIBFT) -lftprintf


clean :
	rm -rf $(OBJ)
	make -C $(LIBFT) clean

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re : fclean all

.PHONY: all clean fclean re
