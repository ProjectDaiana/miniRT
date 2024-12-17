#include "minirt.h"

t_sphere	create_sphere(void)
{
	t_sphere	sphere;

	sphere.center = create_point(0, 0, 0);
	sphere.radius = 1.0;
	sphere.material.ambient = 0.1;
	sphere.material.diffuse = 0.7;
	sphere.material.specular = 0.9;
	sphere.material.shininess = 350;
	sphere.material.reflective = 0.9;
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
	if (((t_sphere *)object)->radius > 0)
		return (normal_at_sphere((t_sphere *)object, world_point));
	else if (((t_plane *)object)->normal.x != 0
		|| ((t_plane *)object)->normal.y != 0
		|| ((t_plane *)object)->normal.z != 0)
		return (normal_at_plane((t_plane *)object, world_point));
	return (create_vector(0, 0, 0));
}
