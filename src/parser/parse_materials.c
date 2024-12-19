#include "minirt.h"

void	init_sphere_material(t_sphere *sphere)
{
	sphere->material.ambient = 0.3;
	sphere->material.diffuse = 0.0;
	sphere->material.specular = 0.2;
	sphere->material.shininess = 300;
	// sphere->material.reflective = 0.7;
	// sphere->material.transparency = 0.9;
}

t_color	create_material_color(char **color_values)
{
	return (create_color(ft_atof(color_values[0]) / 255.0,
			ft_atof(color_values[1]) / 255.0, ft_atof(color_values[2])
			/ 255.0));
}

void	set_color_components(t_color *dest, char **color_values)
{
	dest->r = ft_atof(color_values[0]);
	dest->g = ft_atof(color_values[1]);
	dest->b = ft_atof(color_values[2]);
}
