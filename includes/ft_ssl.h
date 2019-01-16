/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:42:51 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 18:05:33 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"
# include <fcntl.h>
# include <sys/stat.h>

/*
**	OPTIONS:
**		-p: echo STDIN to STDOUT
**		-h: help
**		-c: to output the digest with separating colons
**		-q: quiet mode
**		-r: reverse the format of the output
**		-d: show blocs bits
*/

# define P (1 << 0)
# define D (1 << 1)
# define Q (1 << 2)
# define R (1 << 3)
# define C (1 << 4)
# define E (1 << 5)
# define I (1 << 6)
# define O (1 << 7)
# define A (1 << 8)
# define K (1 << 9)
# define S (1 << 10)
# define V (1 << 11)
# define MAJ_P (1 << 12)
# define L (1 << 13)

# define BLOCK_SIZE_CHAR 64
# define BASE64_1 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrst"
# define BASE64_2 "uvwxyz0123456789+/"
# define BASE64_TABLE BASE64_1 BASE64_2

static int	g_sboxes[8][4][16] = {
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
	},
	{
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
	},
	{
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
	},
	{
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
	},
	{
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
	},
	{
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
	},
	{
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
	},
	{
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
	}
};

static int	g_tab_permute[][64] = {
	{
		57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43,
		35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62,
		54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
	},
	{
		14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
	},
	{
		58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
	},
	{
		32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14,
		15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26,
		27, 28, 29, 28, 29, 30, 31, 32, 1
	},
	{
		16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24,
		14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
	},
	{
		40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
	}
};

typedef enum	e_step
{
	OPTION,
	STRING,
	FILES
}				t_step;

typedef enum	e_algo
{
	NONE = 0,
	MD5 = 1,
	SHA256 = 2,
	BASE_64 = 11,
	DES_ECB = 12,
	DES_CBC = 13,
	DES_CFB = 14,
	DES_OFB = 15,
	DES_CTR = 16,
	DES_PCBC = 17
}				t_algo;

/*
**	Message Digest
*/

typedef struct	s_md5_algo
{
	uint32_t	s[64];
	uint32_t	k[64];
	uint32_t	f;
	int			i;
	int			i_block;
}				t_md5_algo;

typedef struct	s_sha256_algo
{
	uint32_t	k[64];
	uint32_t	w[64];
	uint32_t	f;
	uint32_t	g;
	int			i;
	int			i_block;
}				t_sha256_algo;

typedef	struct	s_hash_info
{
	uint32_t	*hash;
	int			size;
	char		*type;
	int			error;
}				t_hash_info;

typedef struct	s_hash
{
	t_hash_info	info;
	int			i;
	int			lenght_str;
	char		str_block[BLOCK_SIZE_CHAR];
	void		(*apply_algo)(uint32_t *block, u_int32_t **hash);
	int			status;
	uint32_t	block[16];
}				t_hash;

typedef struct	s_datas
{
	char		*str;
	int			is_file;
	void		*next;
}				t_datas;

/*
**	Cipher
*/

typedef struct	s_decode_base64
{
	int			size;
	int			h;
	int			i;
	char		c;
}				t_decode_base64;

typedef struct	s_des_options
{
	char	*key;
	char	*password;
	char	*salt;
	char	*iv;
}				t_des_options;

typedef struct	s_cipher_fd
{
	char		buffer[64];
	int			size_buffer;
	int			ret;
	int			in_fd;
	int			out_fd;
	int			status;
}				t_cipher_fd;

typedef struct	s_cipher_commands
{
	char			*input_file;
	char			*output_file;
	t_des_options	options;
}				t_cipher_commands;

typedef enum	e_permute_type
{
	KEY_PERMUTE,
	SUBKEY_PERMUTE,
	IP_PERMUTE,
	E_PERMUTE,
	P_PERMUTE,
	FINAL_PERMUTE
}				t_permute_type;

typedef struct	s_des
{
	uint64_t			p_key;
	uint64_t			subkey[16];
	uint64_t			ip;
}				t_des;

typedef struct	s_des_info
{
	uint64_t	key;
	uint64_t	salt;
	uint64_t	iv;
	int			show_salt;
	char		buff[32];
	char		size_buffer;
}				t_des_info;

/*
**	General
*/

typedef struct	s_manager
{
	void		*datas;
	int			options;
	t_algo		algo;
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
**	create_block.c
*/

void			create_block(t_hash *hash, char options);

/*
**	md5.c
*/

void			init_md5(t_hash *hash);
void			md5(uint32_t *block, u_int32_t **hash);

/*
**	sha256.c
*/

void			init_sha256(t_hash *hash);
void			sha256(uint32_t *block, u_int32_t **hash);

/*
**	sha256_tools.c
*/

uint32_t		rotr(int n, uint32_t x);
uint32_t		sigma0(uint32_t x);
uint32_t		sigma1(uint32_t x);

/*
**	hash.c
*/

t_hash_info		hash_fd(t_algo	algo, char *str, char options);
t_hash_info		hash(t_algo	algo, char *str, char options);
t_hash_info		hash_with_null(t_algo algo, char *str, char options, int size);

/*
**	read_fd.c
*/

int				read_fd(int fd, char *dest, int size);
int				read_fd_without_space(int fd, char *dest, int size);

/*
**	print_block.c
*/

void			print_block(t_hash *hash, int nbr_block, int is_one_set);

/*
**	print_hash.c
*/

void			print_hash(t_hash_info info, char *str, int is_file,
char options);

/*
**	base64.c
*/

void			base64(t_cipher_fd *cipher, int is_decode);

/*
**	base64_encode.c
*/

void			base64_encode(t_cipher_fd *cipher);
void			base64_encode_str(t_cipher_fd *cipher, char *str, int lenght);

/*
**	base64_decode.c
*/

void			base64_decode(t_cipher_fd *cipher);
int				decode_block(char *str, char *buffer, int lenght);

/*
**	print_optons.c
*/

void			print_cipher_options(void);
void			print_message_digest_options(void);

/*
**	parse_cipher.c
*/

int				parse_cipher(t_manager *m, int ac, char **av);

/*
**	parse_digest.c
*/

int				parse_digest(t_manager *m, int ac, char **av);

/*
**	tools1.c
*/

void			add_vector(t_manager *m, char *str);
void			add_salt(t_manager *m, char *str);
void			add_password(t_manager *m, char *str);

/*
**	tools2.c
*/

void			add_key(t_manager *m, char *str);
void			add_output(t_manager *m, char *str);
void			add_input(t_manager *m, char *str);

/*
**	des.c
*/

void			des(t_cipher_commands *c, t_cipher_fd *cipher, int options,
				t_algo algo);

/*
**	des_tools.c
*/

uint64_t		create_des_block(char *str, int lenght);
void			ft_memcpy_uint64(char *str, uint64_t result);

/*
**	bitwise_operator
*/

uint64_t		bit_extractor(uint64_t number, uint64_t nbr_bit, uint64_t pos);
uint64_t		reverse_u64(uint64_t hash);
uint32_t		reverse_u32(uint32_t hash);

/*
**	register_hex.c
*/

int				register_hex(char *str, uint64_t *value,
				uint64_t value_generated);

/*
**	init_des_info.c
*/

int			init_des_info(t_cipher_commands *c, t_des_info *info, t_algo algo,
int options);
t_hash_info	create_hash(char *password, uint64_t salt);

/*
**	des_value.c
*/

uint64_t		des_value(uint64_t block, t_des_info *info, int is_decode);

/*
**	des_permute.c
*/

uint64_t		permute(uint64_t value, int size_begin, int size_end,
				t_permute_type type);
uint64_t		permute_subkeys(uint64_t ip, uint64_t *subkeys);
uint64_t		f(uint64_t right, uint64_t key);

/*
**	des_encode.c
*/

void			des_encode(t_cipher_fd *cipher, int options,
t_algo algo, t_des_info	*info);


/*
**	des_encode.c
*/

void			des_decode(t_cipher_fd *cipher, int options,
t_algo algo, t_des_info	*info);



/*
**	des_unpermute.c
*/
uint64_t		unpermute(uint64_t value, int size, t_permute_type type);
uint64_t		unpermute_subkeys(uint64_t reverse, uint64_t *subkeys);

#endif
