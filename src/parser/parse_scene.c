/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:37 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/30 19:19:38 by tbella-n         ###   ########.fr       */
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

void	parse_scene(const char *filename, t_scene *scene)
{
	FILE	*file;
	char	line[256];
	char	*newline;
	int		ambient_present;

	ambient_present = 0;
	init_scene_file(filename, &file, scene);
	while (fgets(line, sizeof(line), file))
	{
		newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (!is_valid_line(line))
			continue ;
		if (line[0] == 'A')
			ambient_present = 1;
		parse_line_by_type(line, scene);
	}
	fclose(file);
	if (!ambient_present)
	{
		printf("Error: Scene must contain ambient light\n");
		exit(0);
	}
	if (((scene->sphere_count == 0) && (scene->cylinder_count == 0)
			&& (scene->plane_count == 0)) || scene->light_count == 0)
	{
		printf("Error: Scene must contain at least one shape and one light\n");
		exit(1);
	}
}
