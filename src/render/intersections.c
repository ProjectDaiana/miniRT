#include "minirt.h"

t_intersections	intersect_plane(t_plane plane, t_ray ray)
{
	double			denom;
	t_tuple			p0l0;
	double			t;
	t_intersections	result;

	result.count = 0;
	result.t1 = 0;
	result.t2 = 0;
	denom = tuple_dot(plane.normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		p0l0 = tuple_subtract(plane.point, ray.origin);
		t = tuple_dot(p0l0, plane.normal) / denom;
		if (t >= 0)
		{
			result.count = 1;
			result.t = malloc(sizeof(double));
			result.t[0] = t;
			result.object = malloc(sizeof(void *));
			result.object[0] = &plane;
		}
	}

	return (result);
}

// t_tuple	normal_at_plane(t_plane plane, t_tuple point)
// {
// 	(void)point;
// 	return (plane.normal);
// }

t_tuple	normal_at_plane(t_plane *plane, t_tuple world_point)
{
	(void)world_point;      // Unused parameter
	return (plane->normal); // The normal is constant for a plane
}

void	sort_intersections(t_intersections *xs)
{
	double	temp_t;
	void	*temp_obj;

	for (int i = 0; i < xs->count - 1; i++)
	{
		for (int j = 0; j < xs->count - i - 1; j++)
		{
			if (xs->t[j] > xs->t[j + 1])
			{
				temp_t = xs->t[j];
				xs->t[j] = xs->t[j + 1];
				xs->t[j + 1] = temp_t;
				temp_obj = xs->object[j];
				xs->object[j] = xs->object[j + 1];
				xs->object[j + 1] = temp_obj;
			}
		}
	}
}

// t_intersections	intersect_world(t_scene *scene, t_ray ray)
// {
// 	t_intersections	result;
// 	//int				max_intersections;
// 	t_intersections	sphere_xs;
// 	t_intersections	plane_xs;
// 	t_intersections	cylinder_xs;

// 	result.count = 0;
// 	// max_intersections = scene->sphere_count * 2 + scene->plane_count * 2 + scene->cylinder_count *2;
// 	// result.t = malloc(sizeof(double) * max_intersections);
// 	// result.object = malloc(sizeof(void *) * max_intersections);
// 	//Intersect with spheres
// 	for (int i = 0; i < scene->sphere_count; i++)
// 	{
// 		sphere_xs = intersect_sphere(scene->spheres[i], ray);
// 		for (int j = 0; j < sphere_xs.count; j++)
// 		{
// 			result.t[result.count] = sphere_xs.t[j];
// 			result.object[result.count] = &scene->spheres[i];
// 			result.count++;
// 		}
// 	}
// 	// Intersect with planes
// 	for (int i = 0; i < scene->plane_count; i++)
// 	{
// 		plane_xs = intersect_plane(scene->planes[i], ray);
// 		for (int j = 0; j < plane_xs.count; j++)
// 		{
// 			result.t[result.count] = plane_xs.t[j];
// 			result.object[result.count] = &scene->planes[i];
// 			result.count++;
// 		}
// 	}
// 	//Intersect with cylinders
// 	for (int i = 0; i < scene->cylinder_count; i++)
// 	{
// 		cylinder_xs = intersect_cylinder(scene->cylinders[i], ray);
// 		for (int j = 0; j < cylinder_xs.count; j++)
// 		{
// 			result.t[result.count] = cylinder_xs.t[j];
// 			result.object[result.count] = &scene->cylinders[i];
// 			result.count++;
// 		}
// 		//free_intersections(&cylinder_xs);
// 	}
// 	sort_intersections(&result);

// 	return (result);
// }

void	add_intersection_to_world(t_intersections *xs, double t, void *object)
{
	if (xs->count == 0)
	{
		xs->t = malloc(sizeof(double));
		xs->object = malloc(sizeof(void *));
	}
	else
	{
		// xs->t = realloc(xs->t, sizeof(double) * (xs->count + 1));
		// xs->object = realloc(xs->object, sizeof(void *) * (xs->count + 1));
		
		/// Replacing realloc with ft_calloc and ft_memcpy
		double *new_t = ft_calloc(xs->count + 1, sizeof(double));
        void **new_object = ft_calloc(xs->count + 1, sizeof(void *));
        if (!new_t || !new_object)
        {
            fprintf(stderr, "Error: Memory allocation failed in add_intersection_to_world\n");
            exit(1);
        }

        // Copy existing data to the new memory
        ft_memcpy(new_t, xs->t, sizeof(double) * xs->count);
        ft_memcpy(new_object, xs->object, sizeof(void *) * xs->count);

        // Free the old memory
        free(xs->t);
        free(xs->object);

        // Update the pointers to the new memory
        xs->t = new_t;
        xs->object = new_object;
	}
	if (!xs->t || !xs->object)
    {
        fprintf(stderr, "Error: Memory allocation failed in add_intersection_to_world\n");
        exit(1);
    }
	xs->t[xs->count] = t;
	xs->object[xs->count] = object;
	xs->count++;
}

// // LAST WORKIN VERSION
t_intersections	intersect_world(t_scene *scene, t_ray ray)
{
	t_intersections	result;
	int				max_intersections;
	t_intersections	sphere_xs;
	t_intersections	plane_xs;
	t_intersections	cylinder_xs;

	//init_intersections(&result);
	result.count = 0;
	max_intersections = scene->sphere_count * 2 + scene->plane_count * 2 + scene->cylinder_count *2;
	result.t = ft_calloc(max_intersections, sizeof(double));
	result.object = ft_calloc(max_intersections, sizeof(void *));
	//Intersect with spheres
	for (int i = 0; i < scene->sphere_count; i++)
	{
		sphere_xs = intersect_sphere(scene->spheres[i], ray);
		for (int j = 0; j < sphere_xs.count; j++)
		{
			result.t[result.count] = sphere_xs.t[j];
			result.object[result.count] = &scene->spheres[i];
			result.count++;
		}
		//free_intersections(&sphere_xs); ////// Added
	}
	// Intersect with planes
	for (int i = 0; i < scene->plane_count; i++)
	{
		plane_xs = intersect_plane(scene->planes[i], ray);
		for (int j = 0; j < plane_xs.count; j++)
		{
			result.t[result.count] = plane_xs.t[j];
			result.object[result.count] = &scene->planes[i];
			result.count++;
		}
		//free_intersections(&plane_xs); ////// Added
	}
	//Intersect with cylinders
	for (int i = 0; i < scene->cylinder_count; i++)
	{
		cylinder_xs = intersect_cylinder(scene->cylinders[i], ray);
		for (int j = 0; j < cylinder_xs.count; j++)
		{
			result.t[result.count] = cylinder_xs.t[j];
			result.object[result.count] = &scene->cylinders[i];
			result.count++;
		}
		//free_intersections(&cylinder_xs); ////// Added. One of this is causing the free bad pointer error
	}
	sort_intersections(&result);

	return (result);
}

// t_compu	prepare_computations(double t, t_ray ray, t_intersections *xs)
// {
// 	t_compu	comps;

// 	comps.t = t;
// 	comps.point = position(ray, t);
// 	comps.eyev = tuple_negate(ray.direction);
// 	comps.normalv = normal_at(xs->object[0], comps.point);
// 	if (tuple_dot(comps.normalv, comps.eyev) < 0)
// 	{
// 		comps.inside = 1;
// 		comps.normalv = tuple_negate(comps.normalv);
// 	}
// 	else
// 	{
// 		comps.inside = 0;
// 	}
// 	comps.over_point = tuple_add(comps.point, tuple_multiply(comps.normalv,
// 				EPSILON));
// 	comps.object = xs->object[0];
// 	return (comps);
// }

// t_compu	prepare_computations(double t, t_ray ray, t_intersections *xs)
// {
// 	t_compu	comps;

// 	comps.t = t;
// 	comps.object = xs->object[0];
// 	comps.point = position(ray, t);
// 	comps.eyev = tuple_negate(ray.direction);
// 	comps.normalv = normal_at(comps.object, comps.point);
// 	if (tuple_dot(comps.normalv, comps.eyev) < 0)
// 	{
// 		comps.inside = 1;
// 		comps.normalv = tuple_negate(comps.normalv);
// 	}
// 	else
// 	{
// 		comps.inside = 0;
// 	}
// 	comps.over_point = tuple_add(comps.point, tuple_multiply(comps.normalv,
// 				EPSILON));
// 	return (comps);
// }

// add reflection to the color

t_compu	prepare_computations(double t, t_ray ray, t_intersections *xs)
{
	t_compu	comps;

	comps.t = t;
	comps.object = xs->object[0];
	comps.point = position(ray, t);
	comps.eyev = tuple_negate(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.reflectv = tuple_reflect(ray.direction, comps.normalv);
	if (tuple_dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = tuple_negate(comps.normalv);
	}
	else
	{
		comps.inside = 0;
	}
	comps.over_point = tuple_add(comps.point, tuple_multiply(comps.normalv,
				EPSILON));
	return (comps);
}
