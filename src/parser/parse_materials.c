#include "minirt.h"

void	init_sphere_material(t_sphere *sphere)
{
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.9;
	sphere->material.specular = 0.8;
	sphere->material.shininess = 200;
	sphere->material.reflective = 0.0;
}

t_color	create_material_color(char **color_values)
{
	return (create_color(ft_atof(color_values[0]) / 255.0,
			ft_atof(color_values[1]) / 255.0, ft_atof(color_values[2])
			/ 255.0));
}

void	init_plane_material(t_plane *plane)
{
	plane->material.ambient = 0.15;
	plane->material.diffuse = 0.8;
	plane->material.specular = 0.2;
	plane->material.shininess = 150;
}

void	set_color_components(t_color *dest, char **color_values)
{
	dest->r = ft_atof(color_values[0]);
	dest->g = ft_atof(color_values[1]);
	dest->b = ft_atof(color_values[2]);
}
