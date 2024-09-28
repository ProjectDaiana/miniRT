#include "minirt.h"


void	parse_ambient(char *line, t_scene *scene)
{
	sscanf(line, "A %lf %d,%d,%d", &scene->ambient_intensity,
		&scene->ambient_color.r, &scene->ambient_color.g,
		&scene->ambient_color.b);
	scene->ambient_color.r /= 255.0;
	scene->ambient_color.g /= 255.0;
	scene->ambient_color.b /= 255.0;
}

void	parse_camera(char *line, t_scene *scene)
{
	sscanf(line, "C %lf,%lf,%lf %lf,%lf,%lf %lf", &scene->camera.position.x,
		&scene->camera.position.y, &scene->camera.position.z,
		&scene->camera.orientation.x, &scene->camera.orientation.y,
		&scene->camera.orientation.z, &scene->camera.fov);
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

void	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	sphere;

	sscanf(line, "sp %lf,%lf,%lf %lf %d,%d,%d", &sphere.center.x,
		&sphere.center.y, &sphere.center.z, &sphere.radius,
		&sphere.material.color.r, &sphere.material.color.g,
		&sphere.material.color.b);
	sphere.material.color.r /= 255.0;
	sphere.material.color.g /= 255.0;
	sphere.material.color.b /= 255.0;
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.2;
	sphere.material.shininess = 200.0;
	sphere.radius /= 2.0;
	add_sphere(scene, &sphere);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	cylinder;

	sscanf(line, "cy %lf,%lf,%lf %lf,%lf,%lf %lf %lf %d,%d,%d", &cylinder.center.x,
		&cylinder.center.y, &cylinder.center.z, &cylinder.axis.x,
		&cylinder.axis.y, &cylinder.axis.z, &cylinder.diameter,
		&cylinder.height, &cylinder.color.r, &cylinder.color.g,
		&cylinder.color.b);
	cylinder.color.r /= 255.0;
	cylinder.color.g /= 255.0;
	cylinder.color.b /= 255.0;
	cylinder.material.color = cylinder.color;
	cylinder.material.ambient = 0.1;
	cylinder.material.diffuse = 0.7;
	cylinder.material.specular = 0.2;
	cylinder.material.shininess = 200.0;
	add_cylinder(scene, &cylinder);
}

void	parse_scene(const char *filename, t_scene *scene)
{
	FILE	*file;
	char	line[256];


	file = fopen(filename, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Could not open file %s\n", filename);
		exit(1);
	}
	printf("File opened successfully\n");
	// Initialize scene
	ft_memset(scene, 0, sizeof(t_scene));
	while (fgets(line, sizeof(line), file))
	{

		printf("Parsing line: %s", line);
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
		else if (line[0] == 'c' && line[1] == 'y')
		{
			parse_cylinder(line, scene);
			printf(" Cylinder parsed\n");
			printf(GRN"Cylinder count: %d\n"RESET, scene->cylinder_count);
			printf(GRN"cylinder diameter: %f\n"RESET, scene->cylinders[0].diameter);
			printf(GRN"cylinder height: %f\n"RESET, scene->cylinders[0].height);
			printf(GRN"cylinder axis: %f, %f, %f\n"RESET, scene->cylinders[0].axis.x, scene->cylinders[0].axis.y, scene->cylinders[0].axis.z);
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
