#include "minirt.h"

void	init_scene(t_scene *scene)
{
	// Initialize sphere
	scene->sphere.center = (t_vector){0, 0, 0};
	scene->sphere.radius = 1.0;
	scene->sphere.material.color = (t_color){255, 0, 0};
	scene->sphere.material.diffuse = 0.7;
	scene->sphere.material.specular = 0.3;
	scene->sphere.material.shininess = 100;
	scene->sphere.material.reflective = 0.3;

	// Initialize light
	scene->light.position = (t_vector){-10, 10, -10};
	scene->light.color = (t_color){255, 255, 255};

	// Initialize ambient light
	scene->ambient_color = (t_color){255, 255, 255};
	scene->ambient_intensity = 0.1;
}