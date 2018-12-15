NAME = ft_ssl

SRCSPATH = srcs/
DIGESTPATH = digest/
CIPHERPATH = cipher/
INCLUDES = includes/
HEADERS = ft_ssl.h
LIBFT = libftprintf/
LIBFTINCL = libftprintf/printf/includes/

DIGESTSRCS = datas_tools.c \
			md5.c \
			sha256.c \
			create_block.c \
			hash.c \
			print_block.c \
			print_hash.c \
			sha256_tools.c \
			parse_digest.c

CIPHERSRCS = base64.c \
			des.c \
			parse_cipher.c \
			tools1.c \
			tools2.c \
			register_hex.c \
			init_des_info.c

SRCS = main.c \
	init_datas.c \
	print_options.c \
	read_fd.c \
	bitwise_operator.c \
	$(addprefix $(DIGESTPATH), $(DIGESTSRCS)) \
	$(addprefix $(CIPHERPATH), $(CIPHERSRCS))

SRC = $(addprefix $(SRCSPATH), $(SRCS))

HEADER = $(addprefix $(INCLUDES), $(HEADERS))
WFLAGS = -Wall -Werror -Wextra -fsanitize=address

CC = gcc -g 

OBJ = $(SRC:.c=.o)

all : $(NAME)


libftprintf/libftprintf.a: libftprintf/libft/srcs/ libftprintf/libft/includes/ libftprintf/printf/ libftprintf/libft/includes/ libftprintf/Makefile
	make -C $(LIBFT) all

%.o: %.c $(HEADER)
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
