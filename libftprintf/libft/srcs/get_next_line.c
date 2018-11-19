/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 10:32:07 by bbrunell          #+#    #+#             */
/*   Updated: 2016/01/19 10:32:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_next_4(char **buffer, char **line)
{
	if (*buffer)
		ft_strdel(buffer);
	return (*line[0] != '\0' ? 1 : 0);
}

static void	get_next_1(char **line, char **buffer)
{
	*line = ft_strnew(0);
	*buffer = ft_strnew(BUFF_SIZE);
}

static void	get_next_2(char **line, char **buffer)
{
	char *tmp;
	char *tmp2;

	tmp = *buffer;
	tmp2 = *line;
	*line = ft_strjoin(*line, *buffer);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	*buffer = ft_strnew(BUFF_SIZE);
}

static int	get_next_3(char **line, char **buffer, int ret)
{
	char *tmp;
	char *tmp2;

	if (ret == 0 && *line[0] != '\0')
	{
		ft_strdel(buffer);
		return (1);
	}
	tmp = *buffer;
	*buffer = ft_strsub(*buffer, 0, ret);
	ft_strdel(&tmp);
	tmp = *buffer;
	tmp2 = *line;
	*line = ft_strjoin(*line, *buffer);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	int			ret;
	char		*buffer;
	static char	*str;
	char		*tmp;

	if (fd < 0 || !line)
		return (-1);
	get_next_1(line, &buffer);
	while ((ret = read(fd, buffer, BUFF_SIZE)) >= 0)
	{
		if (ret == 0 && (str == NULL || str[0] == '\0'))
			return (get_next_4(&buffer, line));
		if (str)
		{
			tmp = buffer;
			buffer = ft_strjoin(str, buffer);
			ft_strdel(&str);
			ft_strdel(&tmp);
		}
		((ret = ft_check_end(buffer)) == -1) ? get_next_2(line, &buffer) :
		(str = ft_strsub(buffer, ret + 1, (ft_strlen(buffer) - 1)));
		if (ret != -1)
			return (get_next_3(line, &buffer, ret));
	}
	return (-1);
}
