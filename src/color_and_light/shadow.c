#include "minirt.h"

int	is_shadowed(t_scene *scene, t_tuple point, t_light *light)
{
	t_tuple direction = tuple_subtract(light->position, point);
	double distance = tuple_magnitude(direction);
	t_tuple normalized_direction = tuple_normalize(direction);

	t_ray shadow_ray = create_ray(tuple_add(point,
				tuple_multiply(normalized_direction, EPSILON)),
			normalized_direction);
	t_intersections intersections = intersect_world(scene, shadow_ray);

	for (int i = 0; i < intersections.count; i++)
	{
		if (intersections.t[i] > EPSILON && intersections.t[i] < distance)
		{
			return (1); // Point is in shadow
		}
	}

	return (0); // Point is not in shadow
}
