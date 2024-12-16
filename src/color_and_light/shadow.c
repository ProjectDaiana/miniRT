#include "minirt.h"

int	is_shadowed(t_scene *scene, t_tuple point, t_light *light)
{
	t_tuple			direction;
	double			distance;
	t_tuple			normalized_direction;
	t_ray			shadow_ray;
	t_intersections	intersections;

	direction = tuple_subtract(light->position, point);
	distance = tuple_magnitude(direction);
	normalized_direction = tuple_normalize(direction);
	shadow_ray = create_ray(tuple_add(point,
				tuple_multiply(normalized_direction, EPSILON * 100)),
			normalized_direction);
	intersections = intersect_world(scene, shadow_ray);
	for (int i = 0; i < intersections.count; i++)
	{
		if (intersections.t[i] > distance)
			continue;
		if (intersections.t[i] < EPSILON)
			continue;
		return (1);
	}
	return (0);
}
