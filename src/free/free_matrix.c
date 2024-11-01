#include "minirt.h"

// void	free_matrix(t_matrix *matrix, int size)
// {
// 	int i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		free(matrix->m[i]);
// 		matrix->m[i] = NULL;
// 		i++;
// 	}
// 	free(matrix->m);
// 	matrix->m = NULL;
// }

void	free_mtrx(t_matrix *matrix)
{
	int i;

	i = 0;
	while (i < matrix->size)
	{
		free(matrix->m[i]);
		matrix->m[i] = NULL;
		i++;
	}
	free(matrix->m);
    matrix->m = NULL;
    matrix->size = 0; 
}

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