/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:44:29 by darotche          #+#    #+#             */
/*   Updated: 2024/12/31 10:54:30 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	process_line_and_flags(char *line, t_scene *scene,
		int *element_flags)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!is_valid_line(line))
		return ;
	if (line[0] == 'A')
		*element_flags |= 1;
	else if (line[0] == 'L')
		*element_flags |= 2;
	else if (line[0] == 'C')
		*element_flags |= 4;
	parse_line_by_type(line, scene);
}

void	process_buffer(char *buffer, t_scene *scene, int *element_flags)
{
	char	*start;
	char	*end;

	start = buffer;
	end = ft_strchr(start, '\n');
	while (end)
	{
		*end = '\0';
		process_line_and_flags(start, scene, element_flags);
		start = end + 1;
		end = ft_strchr(start, '\n');
	}
	if (*start)
		process_line_and_flags(start, scene, element_flags);
}

int	process_scene_file(int fd, t_scene *scene)
{
	char	buffer[1024];
	int		element_flags;
	ssize_t	bytes_read;

	element_flags = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		process_buffer(buffer, scene, &element_flags);
	}
	if (bytes_read < 0)
	{
		perror("Error reading file");
		exit(1);
	}
	return (element_flags);
}
