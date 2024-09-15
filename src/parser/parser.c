#include "minirt.h"

int	parse_color(char *str, t_color *color)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	free_split(split);
	return (1);
}

int	parse_vector(char *str, t_tuple *vector)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (0);
	vector->x = atof(split[0]);
	vector->y = atof(split[1]);
	vector->z = atof(split[2]);
	free_split(split);
	return (1);
}

int	parse_ambient(char **split, t_scene *scene)
{
	if (!split[1] || !split[2])
		return (0);
	scene->ambient_intensity = atof(split[1]);
	return (parse_color(split[2], &scene->ambient_color));
}

int	parse_camera(char **split, t_scene *scene)
{
	if (!split[1] || !split[2] || !split[3])
		return (0);
	if (!parse_vector(split[1], &scene->camera.position))
		return (0);
	if (!parse_vector(split[2], &scene->camera.orientation))
		return (0);
	scene->camera.fov = atof(split[3]) * M_PI / 180.0; // Convert to radians
	printf("Parsed camera: pos(%f, %f, %f), orient(%f, %f, %f), fov: %f\n",
		scene->camera.position.x, scene->camera.position.y,
		scene->camera.position.z, scene->camera.orientation.x,
		scene->camera.orientation.y, scene->camera.orientation.z,
		scene->camera.fov);
	return (1);
}

int	parse_light(char **split, t_scene *scene)
{
	if (!split[1] || !split[2] || !split[3])
		return (0);
	if (!parse_vector(split[1], &scene->light.position))
		return (0);
	scene->light.intensity = atof(split[2]);
	return (parse_color(split[3], &scene->light.color));
}

int	parse_sphere(char **split, t_scene *scene)
{
	t_sphere	*sphere;

	if (scene->sphere_count >= MAX_SPHERES)
	{
		printf("Error: Maximum number of spheres reached\n");
		return (0);
	}
	sphere = &scene->spheres[scene->sphere_count];
	if (!split[1] || !split[2] || !split[3])
	{
		printf("Error: Not enough parameters for sphere\n");
		return (0);
	}
	if (!parse_vector(split[1], &sphere->center))
	{
		printf("Error: Invalid center coordinates for sphere\n");
		return (0);
	}
	sphere->radius = atof(split[2]) / 2.0;
	if (!parse_color(split[3], &sphere->material.color))
	{
		printf("Error: Invalid color for sphere\n");
		return (0);
	}
	sphere->material.ambient = scene->ambient_intensity;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.2;
	sphere->material.shininess = 200.0;
	scene->sphere_count++;
	printf("Parsed sphere: center(%f, %f, %f), radius: %f\n", sphere->center.x,
		sphere->center.y, sphere->center.z, sphere->radius);
	return (1);
}

// int	parse_line(char *line, t_scene *scene)
// {
// 	char	**split;

// 	split = ft_split(line, ' ');
// 	if (!split || !split[0])
// 		return (0);
// 	if (ft_strcmp(split[0], "A") == 0)
// 		return (parse_ambient(split, scene));
// 	else if (ft_strcmp(split[0], "C") == 0)
// 		return (parse_camera(split, scene));
// 	else if (ft_strcmp(split[0], "L") == 0)
// 		return (parse_light(split, scene));
// 	else if (ft_strcmp(split[0], "sp") == 0)
// 		return (parse_sphere(split, scene));
// 	free_split(split);
// 	return (0);
// }

int	parse_line(char *line, t_scene *scene)
{
	char	**split;
	int		result;

	result = 0;
	split = ft_split(line, ' ');
	if (!split || !split[0])
		return (0);
	printf("Parsing line type: %s\n", split[0]);
	if (ft_strcmp(split[0], "A") == 0)
		result = parse_ambient(split, scene);
	else if (ft_strcmp(split[0], "C") == 0)
		result = parse_camera(split, scene);
	else if (ft_strcmp(split[0], "L") == 0)
		result = parse_light(split, scene);
	else if (ft_strcmp(split[0], "sp") == 0)
		result = parse_sphere(split, scene);
	else
		printf("Unknown object type: %s\n", split[0]);
	if (!result)
		printf("Failed to parse %s\n", split[0]);
	free_split(split);
	return (result);
}

// int	parse_rt_file(char *filename, t_scene *scene)
// {
// 	int		fd;
// 	char	*line;
// 	int		gnl_result;

// 	printf("Attempting to open file: %s\n", filename);
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (0);
// 	}
// 	printf("File opened successfully\n");
// 	while ((gnl_result = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("Read line: %s\n", line);
// 		if (!parse_line(line, scene))
// 		{
// 			printf("Error parsing line: %s\n", line);
// 			free(line);
// 			close(fd);
// 			return (0);
// 		}
// 		free(line);
// 	}
// 	close(fd);
// 	if (gnl_result == -1)
// 	{
// 		printf("Error in get_next_line\n");
// 		return (0);
// 	}
// 	printf("File parsed successfully\n");
// 	return (1);
// }

int	parse_rt_file(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;
	int		gnl_result;

	printf("Attempting to open file: %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (0);
	}
	printf("File opened successfully\n");
	while ((gnl_result = get_next_line(fd, &line)) > 0)
	{
		printf("Read line: %s\n", line);
		if (!parse_line(line, scene))
		{
			printf("Warning: Failed to parse line: %s\n", line);
			// free(line);
			// close(fd);
			// return (0);
		}
		free(line);
	}
	close(fd);
	if (gnl_result == -1)
	{
		printf("Error in get_next_line\n");
		return (0);
	}

	printf("File parsed successfully\n");
	print_scene_info(scene);
	return (1);
}

void	print_scene_info(t_scene *scene)
{
	printf("Ambient: intensity %.2f, color (%d, %d, %d)\n",
		scene->ambient_intensity, scene->ambient_color.r,
		scene->ambient_color.g, scene->ambient_color.b);
	printf("Camera: position (%.2f, %.2f, %.2f), orientation (%.2f, %.2f,%.2f),FOV %.2f\n", scene->camera.position.x, scene->camera.position.y,
		scene->camera.position.z, scene->camera.orientation.x,
		scene->camera.orientation.y, scene->camera.orientation.z,
		scene->camera.fov);
	printf("Light: position (%.2f, %.2f, %.2f), intensity %.2f, color (%d,%d,%d)\n", scene->light.position.x, scene->light.position.y,
		scene->light.position.z, scene->light.intensity, scene->light.color.r,
		scene->light.color.g, scene->light.color.b);
	printf("Spheres:\n");
	for (int i = 0; i < scene->sphere_count; i++)
	{
		printf("  Sphere %d: center (%.2f, %.2f, %.2f), radius %.2f,color (%d,%d, %d)\n", i + 1, scene->spheres[i].center.x,
			scene->spheres[i].center.y, scene->spheres[i].center.z,
			scene->spheres[i].radius, scene->spheres[i].material.color.r,
			scene->spheres[i].material.color.g,
			scene->spheres[i].material.color.b);
	}
}
