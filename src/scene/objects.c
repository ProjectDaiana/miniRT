#include "minirt.h"

// void	add_light(t_scene *scene, t_light *light)
// {
// 	scene->light_count++;
// 	scene->lights = realloc(scene->lights, scene->light_count
// 			* sizeof(t_light));
// 	scene->lights[scene->light_count - 1] = *light;
// }

// void	add_sphere(t_scene *scene, t_sphere *sphere)
// {
// 	scene->sphere_count++;
// 	scene->spheres = realloc(scene->spheres, scene->sphere_count
// 			* sizeof(t_sphere));
// 	scene->spheres[scene->sphere_count - 1] = *sphere;
// }

// void	add_plane(t_scene *scene, t_plane *plane)
// {
// 	scene->plane_count++;
// 	scene->planes = realloc(scene->planes, scene->plane_count
// 			* sizeof(t_plane));
// 	scene->planes[scene->plane_count - 1] = *plane;
// }

void	add_light(t_scene *scene, t_light *light)
{
	t_light	*new_lights;

	new_lights = ft_calloc(scene->light_count + 1, sizeof(t_light));
	if  (!new_lights)
	{
		fprintf(stderr, "Error: Memory allocation failed for lights\n");
		exit(1);
	}
	if(scene->light_count > 0)
	{
		ft_memcpy(new_lights, scene->lights, scene->light_count * sizeof(t_light));
		free(scene->lights);
	}
	new_lights[scene->light_count] = *light;
	scene->lights = new_lights;
	scene->light_count++;
	printf(GRN"light count: %d\n"RESET, scene->light_count);
}

void	add_plane(t_scene *scene, t_plane *plane)
{
	t_plane *new_planes;

	new_planes = ft_calloc(scene->plane_count + 1, sizeof(t_plane));
	if (!new_planes)
	{
		fprintf(stderr, "Error: Memory allocation failed for planes\n");
		exit(1);
	}
	if (scene->plane_count > 0)
	{
		ft_memcpy(new_planes, scene->planes, scene->plane_count * sizeof(t_plane));
		free(scene->planes);
	}
	new_planes[scene->plane_count] = *plane;
	scene->planes = new_planes;
	scene->plane_count++;
	printf(GRN"plane count: %d\n"RESET, scene->plane_count);
}

void	add_sphere(t_scene *scene, t_sphere *sphere)
{
	t_sphere *new_spheres;

	new_spheres = ft_calloc(scene->sphere_count + 1, sizeof(t_sphere));
	if (!new_spheres)
	{
		fprintf(stderr, "Error: Memory allocation failed for spheres\n");
		exit(1);
	}
	if (scene->sphere_count > 0)
	{
		ft_memcpy(new_spheres, scene->spheres, scene->sphere_count * sizeof(t_sphere));
		free(scene->spheres);
	}
	new_spheres[scene->sphere_count] = *sphere;
	scene->spheres = new_spheres;
	scene->sphere_count++;
	printf(GRN"sphere count: %d\n"RESET, scene->sphere_count);
}

void	add_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_cylinder *new_cylinders;

	new_cylinders = ft_calloc(scene->cylinder_count + 1, sizeof(t_cylinder));
	if (!new_cylinders)
    {
        fprintf(stderr, "Error: Memory allocation failed for cylinders\n");
        exit(1);
    }
	if (scene->cylinder_count > 0)
	{
		ft_memcpy(new_cylinders, scene->cylinders, scene->cylinder_count * sizeof(t_cylinder));
		free(scene->cylinders);
	}
	new_cylinders[scene->cylinder_count] = *cylinder;
	scene->cylinders = new_cylinders;
	scene->cylinder_count++;
	printf(GRN"cylinder count: %d\n"RESET, scene->cylinder_count);
}

// added
t_plane	create_plane(t_tuple point, t_tuple normal, t_color color)
{
	t_plane plane;
	plane.point = point;
	plane.normal = tuple_normalize(normal);
	plane.material.color = color;
	plane.material.ambient = 0.1;
	plane.material.diffuse = 0.9;
	plane.material.specular = 0.9;
	plane.material.shininess = 200.0;
	plane.transform = create_identity_matrix();
	return (plane);
}