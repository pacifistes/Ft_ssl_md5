/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:37:26 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/18 16:34:30 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		base64(t_cipher_fd *cipher, int is_decode)
{
	static void (*apply_algo[])(t_cipher_fd *) = {
		&base64_encode,
		&base64_decode
	};

	(*apply_algo[is_decode])(cipher);
}
