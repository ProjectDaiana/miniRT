/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 20:59:17 by darotche          #+#    #+#             */
/*   Updated: 2024/12/31 01:17:37 by tasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 1024

static char	*ft_get_line(char *left_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}

static int	read_to_left_str(int fd, char **left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	rd_bytes = 1;
	while ((!*left_str || !ft_strchr(*left_str, '\n')) && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (-1);
		}
		buff[rd_bytes] = '\0';
		*left_str = ft_strjoin(*left_str, buff);
	}
	free(buff);
	return (rd_bytes);
}

int	get_next_line(int fd, char **line)
{
	static char	*left_str = NULL;
	int			rd_bytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	rd_bytes = read_to_left_str(fd, &left_str);
	if (rd_bytes == -1)
		return (-1);
	*line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	if (rd_bytes == 0 && !left_str)
		return (0);
	return (1);
}
