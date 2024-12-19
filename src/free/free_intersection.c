#include "minirt.h"

void	free_intersections(t_intersections *xs)
{
	if (xs->t)
	{
		free(xs->t);
		xs->t = NULL;
	}
	if (xs->object)
	{
		free(xs->object);
		xs->object = NULL;
	}
	xs->count = 0;
}

void	free_scene(t_scene *scene)
{
	if (scene->cylinders)
	{
		free(scene->cylinders);
		scene->cylinders = NULL;
	}
	if (scene->planes)
	{
		free(scene->planes);
		scene->planes = NULL;
	}
	if (scene->spheres)
	{
		free(scene->spheres);
		scene->spheres = NULL;
	}
	if (scene->lights)
	{
		free(scene->lights);
		scene->lights = NULL;
	}
}
