#include "minirt.h"

t_sphere	create_sphere(void)
{
	t_sphere	sphere;

	sphere.center = create_point(0, 0, 0);
	sphere.radius = 1.0;
	sphere.material.ambient = 0.2;
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.7;
	sphere.material.shininess = 300;
	sphere.material.reflective = 0.1;
	return (sphere);
}

t_intersections	intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_intersections	result;
	double			params[3];
	double			discriminant;

	calculate_sphere_params(ray, sphere, params);
	discriminant = (params[1] * params[1]) - (4.0 * params[0] * params[2]);
	init_intersection_result(&result, discriminant);
	if (discriminant >= 0)
		set_intersection_values(&result, &sphere, params);
	return (result);
}

t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;

	object_point = tuple_subtract(world_point, sphere->center);
	object_normal = tuple_normalize(object_point);
	if (tuple_dot(object_normal, tuple_subtract(world_point,
				sphere->center)) < 0)
		object_normal = tuple_negate(object_normal);
	return (object_normal);
}

t_tuple	normal_at(void *object, t_tuple world_point)
{
	// t_sphere	*sphere;
	// t_cylinder	*cylinder;
	// t_plane		*plane;
	printf("DEBUG: Checking object type for normal calculation\n");
	// if (((t_cylinder *)object)->diameter > 0)
	// {
	// 	printf("DEBUG: Object identified as cylinder\n");
	// 	return (normal_at_cylinder((t_cylinder *)object, world_point));
	// }
	// sphere = (t_sphere *)object;
	if (((t_sphere *)object)->radius > 0)
	{
		printf("DEBUG: Object identified as sphere\n");
		return (normal_at_sphere((t_sphere *)object, world_point));
	}
	if (((t_cylinder *)object)->diameter > 0)
	{
		printf("DEBUG: Object identified as cylinder\n");
		return (normal_at_cylinder((t_cylinder *)object, world_point));
	}
	// plane = (t_plane *)object;
	if (((t_plane *)object)->normal.x != 0 || ((t_plane *)object)->normal.y != 0
		|| ((t_plane *)object)->normal.z != 0)
	{
		printf("DEBUG: Object identified as plane\n");
		return (normal_at_plane((t_plane *)object, world_point));
	}
	// cylinder = (t_cylinder *)object;
	printf("DEBUG: Object type not identified!\n");
	return (create_vector(0, 0, 0));
}

// t_tuple	normal_at(void *object, t_tuple world_point)
// {
// 	t_sphere *sphere;
// 	t_plane *plane;
// 	t_cylinder *cylinder;
// 	double normal_length;

// 	// Match the working order from get_object_material
// 	sphere = (t_sphere *)object;
// 	if (sphere->radius > 0 && sphere->center.w == 1.0)
// 		return (normal_at_sphere(sphere, world_point));

// 	plane = (t_plane *)object;
// 	normal_length = sqrt(plane->normal.x * plane->normal.x + plane->normal.y
// 			* plane->normal.y + plane->normal.z * plane->normal.z);
// 	if (fabs(normal_length - 1.0) < EPSILON)
// 		return (normal_at_plane(plane, world_point));

// 	cylinder = (t_cylinder *)object;
// 	return (normal_at_cylinder(cylinder, world_point));
// }
