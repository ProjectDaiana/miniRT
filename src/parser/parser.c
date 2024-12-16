#include "minirt.h"

// void	parse_ambient(char *line, t_scene *scene)
// {
// 	sscanf(line, "A %lf %d,%d,%d", &scene->ambient_intensity,
// 		&scene->ambient_color.r, &scene->ambient_color.g,
// 		&scene->ambient_color.b);
// 	scene->ambient_color.r /= 255.0;
// 	scene->ambient_color.g /= 255.0;
// 	scene->ambient_color.b /= 255.0;
// }

// void	parse_camera(char *line, t_scene *scene)
// {
// 	sscanf(line, "C %lf,%lf,%lf %lf,%lf,%lf %lf", &scene->camera.position.x,
// 		&scene->camera.position.y, &scene->camera.position.z,
// 		&scene->camera.orientation.x, &scene->camera.orientation.y,
// 		&scene->camera.orientation.z, &scene->camera.fov);
// }

void	parse_ambient(char *line, t_scene *scene)
{
	char	**split;
	char	**color;

	split = ft_split(line, ' ');
	if (!split || !split[1] || !split[2])
	{
		fprintf(stderr, "Error: Invalid ambient light format\n");
		return ;
	}
	scene->ambient_intensity = ft_atof(split[1]);
	color = ft_split(split[2], ',');
	if (!color || !color[0] || !color[1] || !color[2])
	{
		fprintf(stderr, "Error: Invalid ambient light color format\n");
		ft_free_split(split);
		return ;
	}
	scene->ambient_color.r = ft_atof(color[0]) / 255.0;
	scene->ambient_color.g = ft_atof(color[1]) / 255.0;
	scene->ambient_color.b = ft_atof(color[2]) / 255.0;
	ft_free_split(split);
	ft_free_split(color);
}

void	parse_camera(char *line, t_scene *scene)
{
	char	**split;
	char	**pos;
	char	**orient;

	split = ft_split(line, ' ');
	if (!split || !split[1] || !split[2] || !split[3])
	{
		fprintf(stderr, "Error: Invalid camera format\n");
		return ;
	}
	pos = ft_split(split[1], ',');
	orient = ft_split(split[2], ',');
	if (!pos || !pos[0] || !pos[1] || !pos[2] || !orient || !orient[0]
		|| !orient[1] || !orient[2])
	{
		fprintf(stderr,
			"Error: Invalid camera position or orientation format\n");
		ft_free_split(split);
		return ;
	}
	scene->camera.position = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
	scene->camera.orientation = create_vector(ft_atof(orient[0]),
			ft_atof(orient[1]), ft_atof(orient[2]));
	scene->camera.fov = ft_atof(split[3]);
	ft_free_split(split);
	ft_free_split(pos);
	ft_free_split(orient);
}

void	parse_light(char *line, t_scene *scene)
{
	t_light	light;

	sscanf(line, "L %lf,%lf,%lf %lf %d,%d,%d", &scene->light.position.x,
		&scene->light.position.y, &scene->light.position.z,
		&scene->light.intensity, &scene->light.color.r, &scene->light.color.g,
		&scene->light.color.b);
	light.color.r /= 255.0;
	light.color.g /= 255.0;
	light.color.b /= 255.0;
	add_light(scene, &light);
}

// void	parse_sphere(char *line, t_scene *scene)
// {
// 	t_sphere	sphere;
// 	int			ret;

// 	ret = sscanf(line, "sp %lf,%lf,%lf %lf %d,%d,%d %lf", &sphere.center.x,
// 			&sphere.center.y, &sphere.center.z, &sphere.radius,
// 			&sphere.material.color.r, &sphere.material.color.g,
// 			&sphere.material.color.b, &sphere.material.reflective);
// 	printf("Parsing line: %s\n", line);
// 	printf("sscanf read %d values\n", ret); // Should be 8
// 	printf("Parsed values:\n");
// 	printf("Position: %f,%f,%f\n", sphere.center.x, sphere.center.y,
// 		sphere.center.z);
// 	printf("Radius: %f\n", sphere.radius);
// 	printf("Color: %d,%d,%d\n", sphere.material.color.r,
// 		sphere.material.color.g, sphere.material.color.b);
// 	printf("Reflective: %f\n", sphere.material.reflective);
// 	if (ret != 8)
// 		printf("Error: Failed to parse all sphere values (expected 8,						got			%d)\n",ret);
// sphere.material.color.r/= 255.0;
// sphere.material.color.g/= 255.0;
// sphere.material.color.b
//	/= 255.0;
// 	sphere.material.ambient = 0.1;
// 	sphere.material.diffuse = 0.7;
// 	// sphere.material.specular = 0.2;
// 	sphere.material.specular = 1.0;
// 	sphere.material.shininess = 3000.0;
// 	// sphere.material.reflective = 0.5;
// 	sphere.radius /= 2.0;
// 	add_sphere(scene, &sphere);
// }

void	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	sphere;
	char		**split;
	char		**color;
	char		**pos;

	// char		*reflective_str;
	split = ft_split(line, ' ');
	if (!split || !split[1] || !split[2] || !split[3] || !split[4])
	// Check for reflective value
	{
		fprintf(stderr, "Error: Invalid sphere format\n");
		return ;
	}
	// Parse position
	pos = ft_split(split[1], ',');
	if (!pos || !pos[0] || !pos[1] || !pos[2])
	{
		fprintf(stderr, "Error: Invalid sphere position format\n");
		ft_free_split(split);
		return ;
	}
	sphere.center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
	// Parse radius
	sphere.radius = ft_atof(split[2]) / 2.0;
	// Parse color
	color = ft_split(split[3], ',');
	if (!color || !color[0] || !color[1] || !color[2])
	{
		fprintf(stderr, "Error: Invalid sphere color format\n");
		ft_free_split(split);
		ft_free_split(pos);
		return ;
	}
	sphere.material.color = create_color(ft_atof(color[0]) / 255.0,
			ft_atof(color[1]) / 255.0, ft_atof(color[2]) / 255.0);
	// Parse reflective value
	sphere.material.reflective = ft_atof(split[4]);
	// Set other material properties
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.9;
	sphere.material.shininess = 200.0;
	add_sphere(scene, &sphere);
	ft_free_split(split);
	ft_free_split(pos);
	ft_free_split(color);
}

void	parse_plane(char *line, t_scene *scene)
{
	t_plane	plane;

	t_tuple point, normal;
	int r, g, b;
	sscanf(line, "pl %lf,%lf,%lf %lf,%lf,%lf %d,%d,%d", &point.x, &point.y,
		&point.z, &normal.x, &normal.y, &normal.z, &r, &g, &b);
	plane = create_plane(point, normal, create_color(r / 255.0, g / 255.0, b
				/ 255.0));
	plane.material.ambient = 0.1;
	plane.material.diffuse = 0.9;
	plane.material.specular = 0.9;
	plane.material.shininess = 200.0;
	add_plane(scene, &plane);
}

void	parse_scene(const char *filename, t_scene *scene)
{
	FILE	*file;
	char	line[256];

	file = fopen(filename, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open file %s\n ", filename);
		exit(1);
	}
	printf("File opened successfully\n");
	// Initialize scene
	ft_memset(scene, 0, sizeof(t_scene));
	while (fgets(line, sizeof(line), file))
	{
		printf("Parsing line: %s ", line);
		if (line[0] == 'A')
		{
			parse_ambient(line, scene);
			printf(" Ambient light parsed\n");
		}
		else if (line[0] == 'C')
		{
			parse_camera(line, scene);
			printf(" Camera parsed\n");
		}
		else if (line[0] == 'L')
		{
			parse_light(line, scene);
			printf(" Light parsed\n");
		}
		else if (line[0] == 's' && line[1] == 'p')
		{
			parse_sphere(line, scene);
			printf(" Sphere parsed\n");
		}
		else if (line[0] == 'p' && line[1] == 'l')
		{
			parse_plane(line, scene);
			printf(" Plane parsed\n");
		}
	}
	fclose(file);
	if (scene->sphere_count == 0 || scene->light_count == 0)
	{
		fprintf(stderr,
			"Error: Scene must contain at least one sphere and one light\n");
		exit(1);
	}
	printf("Scene parsed successfully\n");
}

