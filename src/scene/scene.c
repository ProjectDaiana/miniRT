#include "minirt.h"

void	init_scene(t_scene *scene)
{
	// Initialize sphere
	scene->sphere.center = (t_tuple){0, 1, 5, 1};          // Move sphere forward
	scene->sphere.radius = 2.0;                          // Make sphere larger
	scene->sphere.material.color = (t_color){255, 0, 0}; // Red
	scene->sphere.material.diffuse = 0.7;
	scene->sphere.material.specular = 0.3;
	scene->sphere.material.shininess = 60;
	scene->sphere.material.reflective = 0.1;
	scene->sphere_count = 1 ;
	// Initialize light
	scene->light.position = (t_tuple){-5, 5, -5, 1};
	scene->light.color = (t_color){255, 255, 255};
	// Initialize ambient light
	scene->ambient_color = (t_color){255, 255, 255};
	scene->ambient_intensity = 0.1;
}

t_hit	intersect_scene(t_ray ray, t_scene *scene)
{
	t_hit closest_hit, current_hit;
	int i;

	closest_hit.hit = 0;
	closest_hit.t = INFINITY;
	init_scene(scene);
	for (i = 0; i < scene->sphere_count; i++)
	{
		current_hit = intersect_sphere(ray, scene->spheres[i]);
		if (current_hit.hit && current_hit.t < closest_hit.t)
		{
			closest_hit = current_hit;
		}
	}
	return (closest_hit);
}
