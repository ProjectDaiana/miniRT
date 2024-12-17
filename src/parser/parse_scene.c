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
		printf("Parsing line: [%s]\n", line);
		parse_line_by_type(line, scene);
	}
	fclose(file);
	if (scene->sphere_count == 0 || scene->light_count == 0)
	{
		printf("Error: Scene must contain at least one sphere and one light\n");
		exit(1);
	}
}

t_plane	create_plane_from_params(char **pos, char **normal, char **color)
{
	t_plane	plane;
	t_tuple	point;
	t_tuple	norm;

	point = create_point(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	norm = create_vector(ft_atof(normal[0]), ft_atof(normal[1]),
			ft_atof(normal[2]));
	plane = create_plane(point, norm, create_material_color(color));
	init_plane_material(&plane);
	return (plane);
}
