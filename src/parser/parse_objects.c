#include "minirt.h"

void	set_camera_orientation(t_scene *scene, char **orient)
{
	scene->camera.orientation = create_vector(ft_atof(orient[0]),
			ft_atof(orient[1]), ft_atof(orient[2]));
}

void	set_camera_position(t_scene *scene, char **pos)
{
	scene->camera.position = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
}

void	set_sphere_center(t_sphere *sphere, char **pos)
{
	sphere->center = create_point(ft_atof(pos[0]), ft_atof(pos[1]),
			ft_atof(pos[2]));
}

int	init_plane_splits(char *line, char ***split, char ***pos,
		char ***normal)
{
	*split = ft_split(line, ' ');
	if (!validate_params(*split, 4, "plane"))
		return (0);
	*pos = ft_split((*split)[1], ',');
	*normal = ft_split((*split)[2], ',');
	if (!validate_coordinates(*pos, "plane", *split)
		|| !validate_coordinates(*normal, "plane normal", *split))
	{
		free_splits(*split, *pos, *normal);
		return (0);
	}
	return (1);
}

int	init_plane_color(char **split, char ***color)
{
	*color = ft_split(split[3], ',');
	if (!validate_coordinates(*color, "plane color", split))
	{
		ft_free_split(*color);
		return (0);
	}
	return (1);
}
