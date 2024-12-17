#include "minirt.h"

static void	init_plane_material(t_plane *plane, t_color color)
{
	plane->material.color = color;
	plane->material.ambient = 0.15;
	plane->material.diffuse = 0.8;
	plane->material.specular = 0.2;
	plane->material.shininess = 200;
	plane->material.reflective = 0.05;
}

static void	set_plane_pattern(t_plane *plane)
{
	t_color		white;
	t_color		black;
	t_matrix	scale;

	white = create_color(1.0, 1.0, 1.0);
	black = create_color(0.0, 0.0, 0.0);
	plane->material.pattern = create_checkers_pattern(white, black);
	scale = scaling(1.0, 1.0, 1.0);
	plane->material.pattern.transform = scale;
}

t_plane	create_plane(t_tuple point, t_tuple normal, t_color color)
{
	t_plane	plane;

	plane.point = point;
	plane.normal = tuple_normalize(normal);
	plane.transform = create_identity_matrix();
	init_plane_material(&plane, color);
	set_plane_pattern(&plane);
	return (plane);
}
