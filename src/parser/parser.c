#include "minirt.h"

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
	if (!validate_params(split, 4, "camera"))
		return ;
	pos = ft_split(split[1], ',');
	orient = ft_split(split[2], ',');
	if (!validate_coordinates(pos, "camera", split)
		|| !validate_coordinates(orient, "camera orientation", split))
	{
		free_splits(pos, orient, NULL);
		return ;
	}
	set_camera_position(scene, pos);
	set_camera_orientation(scene, orient);
	scene->camera.fov = ft_atof(split[3]);
	free_splits(split, pos, orient);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**split;
	char	**pos;
	char	**color;

	split = ft_split(line, ' ');
	if (!validate_params(split, 4, "light"))
		return ;
	pos = ft_split(split[1], ',');
	if (!validate_coordinates(pos, "light", split))
		return ;
	scene->light.position.x = ft_atof(pos[0]);
	scene->light.position.y = ft_atof(pos[1]);
	scene->light.position.z = ft_atof(pos[2]);
	scene->light.position.w = 1.0;
	scene->light.intensity = ft_atof(split[2]) * 1.2;
	color = ft_split(split[3], ',');
	if (!validate_coordinates(color, "light color", split))
	{
		ft_free_split(pos);
		return ;
	}
	set_color_components(&scene->light.color, color);
	scene->light_count++;
	free_splits(split, pos, color);
}

void	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	sphere;
	char		**split;
	char		**color;
	char		**pos;

	split = ft_split(line, ' ');
	if (!validate_params(split, 4, "sphere"))
		return ;
	pos = ft_split(split[1], ',');
	if (!validate_coordinates(pos, "sphere", split))
		return ;
	set_sphere_center(&sphere, pos);
	sphere.radius = ft_atof(split[2]) / 2.0;
	color = ft_split(split[3], ',');
	if (!validate_coordinates(color, "sphere color", split))
	{
		ft_free_split(pos);
		return ;
	}
	sphere.material.color = create_material_color(color);
	init_sphere_material(&sphere);
	add_sphere(scene, &sphere);
	free_splits(split, pos, color);
}

void	parse_plane(char *line, t_scene *scene)
{
	t_plane	plane;
	char	**split;
	char	**pos;
	char	**normal;
	char	**color;

	if (!init_plane_splits(line, &split, &pos, &normal))
		return ;
	if (!init_plane_color(split, &color))
	{
		free_splits(split, pos, normal);
		return ;
	}
	plane = create_plane_from_params(pos, normal, color);
	add_plane(scene, &plane);
	free_splits(split, pos, normal);
	ft_free_split(color);
}
