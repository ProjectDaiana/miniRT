/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:37 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 20:49:21 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene_file(const char *filename, FILE **file, t_scene *scene)
{
	const char	*extension = strrchr(filename, '.');

	*file = fopen(filename, "rt");
	if (!extension || strcmp(extension, ".rt") != 0)
	{
		fprintf(stderr, "Error: Invalid file extension. Expected '.rt'\n");
		exit(1);
	}
	if (!*file)
	{
		fprintf(stderr, "Error: Could not open file %s\n ", filename);
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
	if (!(element_flags & (1 << 0)) || !(element_flags & (1 << 1))
		|| !(element_flags & (1 << 2)))
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

int	process_scene_file(FILE *file, t_scene *scene)
{
	char	line[256];
	char	*newline;
	int		element_flags;

	element_flags = 0;
	while (fgets(line, sizeof(line), file))
	{
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (!is_valid_line(line))
			continue ;
		if (line[0] == 'A')
			element_flags |= 1 << 0;
		else if (line[0] == 'L')
			element_flags |= 1 << 1;
		else if (line[0] == 'C')
			element_flags |= 1 << 2;
		parse_line_by_type(line, scene);
	}
	return (element_flags);
}

void	parse_scene(const char *filename, t_scene *scene)
{
	FILE	*file;
	int		element_flags;

	init_scene_file(filename, &file, scene);
	element_flags = process_scene_file(file, scene);
	fclose(file);
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
