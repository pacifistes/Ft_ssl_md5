/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:51:43 by bbrunell          #+#    #+#             */
/*   Updated: 2016/09/14 16:25:56 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*end_trim(char const *s, int i, int j, int len)
{
	char	*trim;

	trim = ft_strnew(len - i + 1);
	if (trim == NULL)
		return (NULL);
	j = 0;
	while (s[i] && i <= len)
	{
		trim[j] = s[i];
		i++;
		j++;
	}
	trim[j] = '\0';
	return (trim);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	j = len;
	if (!s || len == 0)
		return (ft_strnew(0));
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	len--;
	while ((s[len] == ' ' || s[len] == '\n' || s[len] == '\t') && len >= 0)
		len--;
	if (!s[i])
		return (ft_strnew(0));
	return (end_trim(s, i, j, len));
}
