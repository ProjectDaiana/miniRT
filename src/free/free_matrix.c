#include "minirt.h"

void	free_matrix(t_matrix *matrix)
{
	int i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		i++;
	}
	free(matrix->m);
}

// void free_intersections(t_intersections *result)
// {
//     if (result->t != NULL)
//     {
//         free(result->t);
//         result->t = NULL;
//     }
//     if (result->object != NULL)
//     {
//         free(result->object);
//         result->object = NULL;
//     }
// }

void free_scene(t_scene *scene)
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

void free_intersections(t_intersections *intersections)
{
	free(intersections->t);
	free(intersections->object);
	intersections->t = NULL;
	intersections->object = NULL;
	intersections->count = 0;
	intersections->capacity = 0;
	//printf(MAG"Freed intersections\n"RESET);
}

void free_all_intersections(t_intersections *intersections)
{
	int i;

	i = 0;
	while (i < intersections->count)
	{
		free(intersections->object[i]);
		i++;
	}
	free(intersections->t);
	free(intersections->object);
	intersections->t = NULL;
	intersections->object = NULL;
	intersections->count = 0;
	intersections->capacity = 0;
	//printf(MAG"Freed all intersections\n"RESET);
}