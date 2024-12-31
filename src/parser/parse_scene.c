/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:37 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/31 10:54:46 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	validate_and_open_file(const char *filename)
{
	const char	*extension = ft_strrchr(filename, '.');
	int			fd;
	char		test_buf[1];

	if (!extension || ft_strcmp(extension, ".rt") != 0)
	{
		printf("Error: Invalid file extension. Expected '.rt'\n");
		exit(1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	if (read(fd, test_buf, 1) < 0)
	{
		perror("Error reading file");
		close(fd);
		exit(1);
	}
	return (fd);
}

void	init_scene_file(const char *filename, int *fd, t_scene *scene)
{
	close(*fd = validate_and_open_file(filename));
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		perror("Error reopening file");
		exit(1);
	}
	ft_memset(scene, 0, sizeof(t_scene));
}

void	parse_line_by_type(char *line, t_scene *scene)
{
	if (line[0] == 'A')
		parse_ambient(line, scene);
	else if (line[0] == 'C')
		parse_camera(line, scene);
	else if (line[0] == 'L')
		parse_light(line, scene);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(line, scene);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_plane(line, scene);
	else if (line[0] == 'c' && line[1] == 'y')
		parse_cylinder(line, scene);
}

void	validate_scene_elements(t_scene *scene, int element_flags)
{
	if (!(element_flags & 1) || !(element_flags & 2) || !(element_flags & 4))
	{
		printf("Error: Scene must contain A, L and C\n");
		exit(1);
	}
	if (((scene->sphere_count == 0) && (scene->cylinder_count == 0)
			&& (scene->plane_count == 0)) || scene->light_count == 0)
	{
		printf("Error: Scene must contain at least one shape and one light\n");
		exit(1);
	}
}

void	parse_scene(const char *filename, t_scene *scene)
{
	int	fd;
	int	element_flags;

	init_scene_file(filename, &fd, scene);
	element_flags = process_scene_file(fd, scene);
	close(fd);
	validate_scene_elements(scene, element_flags);
}
