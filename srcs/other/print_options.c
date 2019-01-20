/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:26:59 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/19 14:41:05 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_message_digest_options(void)
{
	ft_printf("Message Digest commands: Error in parameters.\n");
	ft_printf("Usage: ./ft_ssl sha256|md5 [-pcqdr] [-s string ...]");
	ft_printf(" [file ...]\noptions are\n");
	ft_printf("%-4s to output the digest with separating colons\n", "-c");
	ft_printf("%-4s to display blocs's info\n", "-d");
	ft_printf("%-4s echo STDIN to STDOUT and append the checksum", "-p");
	ft_printf(" to STDOUT\n");
	ft_printf("%-4s quiet mode\n", "-q");
	ft_printf("%-4s reverse the format of the output\n", "-r");
	ft_printf("%-4s print the sum of the given string\n", "-s");
}

void	print_cipher_options(void)
{
	ft_printf("Cipher commands: Error in parameters.\n");
	ft_printf("options are:\n");
	ft_printf("base64\n");
	ft_printf("%-12s decode mode\n", "-d");
	ft_printf("%-12s encode mode (default)\n", "-e");
	ft_printf("%-12s input file\n", "-i <file>");
	ft_printf("%-12s output file\n\n", "-o <file>");
	ft_printf("des/des-ecb/des-cbc/des-cfb/des-ofb/des-ctr/des-pcbc\n");
	ft_printf("%-16s decode/encode the input/output in base64,", "-a");
	ft_printf(" depending on the encrypt mode\n");
	ft_printf("%-16s decrypt mode\n", "-d");
	ft_printf("%-16s encrypt mode (default)\n", "-e");
	ft_printf("%-16s input file\n", "-i <file>");
	ft_printf("%-16s output file\n", "-o <file>");
	ft_printf("%-16s key in hex\n", "-k <key>");
	ft_printf("%-16s password in ascii\n", "-p <password>");
	ft_printf("%-16s salt in hex\n", "-s <salt>");
	ft_printf("%-16s vector in hex\n", "-v <vector>");
	ft_printf("%-16s see salt and key generated\n", "-P");
}
