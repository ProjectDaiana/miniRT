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
	sphere.material.color = create_material_color(color);
	// printf("DEBUG Sphere: Creating sphere with color: R=%d, G=%d, B=%d\n",
	// 	sphere.material.color.r ,sphere.material.color.g
	// 		, sphere.material.color.b);
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
	int		param_count;

	split = ft_split(line, ' ');
	param_count = 0;
	while (split[param_count])
		param_count++;
	if (!init_plane_splits(line, &split, &pos, &normal))
		return ;
	if (!init_plane_color(split, &color))
	{
		free_splits(split, pos, normal);
		return ;
	}
	plane = create_plane_from_params(pos, normal, color);
	if (param_count > 4)
		plane.material.reflective = ft_atof(split[4]);
	if (param_count > 5)
		plane.material.transparency = ft_atof(split[5]);
	add_plane(scene, &plane);
	free_splits(split, pos, normal);
	ft_free_split(color);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	cylinder;
	char		**split;
	char		**pos;
	char		**orient;
	char		**color;

	split = ft_split(line, ' ');
	if (!validate_params(split, 5, "cylinder"))
		return ;
	pos = ft_split(split[1], ',');
	orient = ft_split(split[2], ',');
	if (!validate_coordinates(pos, "cylinder position", split)
		|| !validate_coordinates(orient, "cylinder orientation", split))
	{
		free_splits(split, pos, orient);
		return ;
	}
	cylinder.center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
	cylinder.axis = create_vector(ft_atof(orient[0]), ft_atof(orient[1]),
			ft_atof(orient[2]));
	cylinder.axis = tuple_normalize(cylinder.axis);
	cylinder.diameter = ft_atof(split[3]);
	cylinder.height = ft_atof(split[4]);
	color = ft_split(split[5], ',');
	if (!validate_coordinates(color, "cylinder color", split))
	{
		free_splits(split, pos, orient);
		return ;
	}
	cylinder.material.color = create_material_color(color);
	cylinder.min = 0;
	cylinder.max = cylinder.height;
	cylinder.material.ambient = 0.2;
	cylinder.material.diffuse = 0.9;
	cylinder.material.specular = 0.1;
	cylinder.material.shininess = 100;
	cylinder.material.reflective = 0.0;
	cylinder.material.has_pattern = 0.0;
	// printf("DEBUG: Creating cylinder with normalized color: R=%d, G=%d, B=%d\n",
		// cylinder.material.color.r, cylinder.material.color.g,
		// cylinder.material.color.b);
	add_cylinder(scene, &cylinder);
	free_splits(split, pos, orient);
	ft_free_split(color);
}
