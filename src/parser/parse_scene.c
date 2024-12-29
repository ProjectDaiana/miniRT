/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:37 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 21:35:09 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene_file(const char *filename, FILE **file, t_scene *scene)
{
	*file = fopen(filename, "r");
	if (!*file)
	{
		fprintf(stderr, "Error: Could not open file %s\n ", filename);
		exit(1);
	}
	printf("File opened successfully, initializing scene\n");
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

void	parse_scene(const char *filename, t_scene *scene)
{
	FILE	*file;
	char	line[256];
	char	*newline;

	init_scene_file(filename, &file, scene);
	while (fgets(line, sizeof(line), file))
	{
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (!is_valid_line(line))
			continue ;
		parse_line_by_type(line, scene);
	}
	fclose(file);
	if (((scene->sphere_count == 0) && (scene->cylinder_count == 0)
			&& (scene->plane_count == 0)) || scene->light_count == 0)
	{
		printf("Error: Scene must contain at least one shape and one light\n");
		exit(1);
	}
	printf("Scene contents:\n");
	printf("Camera: pos(%.2f,%.2f,%.2f) dir(%.2f,%.2f,%.2f) fov %.2f\n",
		scene->camera.position.x, scene->camera.position.y,
		scene->camera.position.z, scene->camera.orientation.x,
		scene->camera.orientation.y, scene->camera.orientation.z,
		scene->camera.fov);
	printf("Spheres: %d\n", scene->sphere_count);
	printf("Planes: %d\n", scene->plane_count);
	printf("Cylinders: %d\n", scene->cylinder_count);
}
