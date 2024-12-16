#include "minirt.h"

void	add_light(t_scene *scene, t_light *light)
{
	scene->light_count++;
	scene->lights = realloc(scene->lights, scene->light_count
			* sizeof(t_light));
	scene->lights[scene->light_count - 1] = *light;
}
// ok
void	add_sphere(t_scene *scene, t_sphere *sphere)
{
	scene->sphere_count++;
	scene->spheres = realloc(scene->spheres, scene->sphere_count
			* sizeof(t_sphere));
	scene->spheres[scene->sphere_count - 1] = *sphere;
}

void	add_plane(t_scene *scene, t_plane *plane)
{
	scene->plane_count++;
	scene->planes = realloc(scene->planes, scene->plane_count
			* sizeof(t_plane));
	scene->planes[scene->plane_count - 1] = *plane;
}

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	scene->cylinder_count++;
	scene->cylinders = realloc(scene->cylinders, scene->cylinder_count
			* sizeof(t_cylinder));
	scene->cylinders[scene->cylinder_count - 1] = *cylinder;
}

// added
t_plane	create_plane(t_tuple point, t_tuple normal, t_color color)
{
	t_plane	plane;

	plane.point = point;
	plane.normal = tuple_normalize(normal);
	plane.material.color = color;
	plane.material.ambient = 0.1;
	plane.material.diffuse = 0.9;
	plane.material.specular = 0.0;
	plane.material.shininess = 200;
	plane.material.reflective = 0.0;
	plane.transform = create_identity_matrix();
	return (plane);
}
