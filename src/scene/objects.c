#include "minirt.h"

void	add_light(t_scene *scene, t_light *light)
{
	scene->light_count++;
	scene->lights = realloc(scene->lights, scene->light_count
			* sizeof(t_light));
	scene->lights[scene->light_count - 1] = *light;
}

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
	scene->cylinders[scene->cylinder_count - 1].max = scene->cylinders[scene->cylinder_count - 1].height / 2;
	scene->cylinders[scene->cylinder_count - 1].min = 2;
}