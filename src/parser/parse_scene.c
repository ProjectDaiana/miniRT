/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasha <tasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:37 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/31 02:51:18 by tasha            ###   ########.fr       */
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

static void	process_line_and_flags(char *line, t_scene *scene,
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

static void	process_buffer(char *buffer, t_scene *scene, int *element_flags)
{
	char	*start;
	char	*end;

	start = buffer;
	while ((end = ft_strchr(start, '\n')))
	{
		*end = '\0';
		process_line_and_flags(start, scene, element_flags);
		start = end + 1;
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
	while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
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

void	parse_scene(const char *filename, t_scene *scene)
{
	int	fd;
	int	element_flags;

	init_scene_file(filename, &fd, scene);
	element_flags = process_scene_file(fd, scene);
	close(fd);
	validate_scene_elements(scene, element_flags);
}

// void	parse_scene(const char *filename, t_scene *scene)
// {
// 	FILE	*file;
// 	char	line[256];
// 	char	*newline;
// 	int		ambient_present;
// 	int		light_present;
// 	int		camera_present;

// 	ambient_present = 0;
// 	light_present = 0;
// 	camera_present = 0;
// 	init_scene_file(filename, &file, scene);
// 	while (fgets(line, sizeof(line), file))
// 	{
// 		newline = strchr(line, '\n');
// 		if (newline)
// 			*newline = '\0';
// 		if (!is_valid_line(line))
// 			continue ;
// 		if (line[0] == 'A')
// 			ambient_present = 1;
// 		else if (line[0] == 'L')
// 			light_present = 1;
// 		else if (line[0] == 'C')
// 			camera_present = 1;
// 		parse_line_by_type(line, scene);
// 	}
// 	fclose(file);
// 	if (!ambient_present || !light_present || !camera_present)
// 	{
// 		printf("Error: Scene must contain A, L and C\n");
// 		exit(0);
// 	}
// 	if (((scene->sphere_count == 0) && (scene->cylinder_count == 0)
// 			&& (scene->plane_count == 0)) || scene->light_count == 0)
// 	{
// 		printf("Error: Scene must contain at least one shape and one light\n");
// 		exit(1);
// 	}
// }
