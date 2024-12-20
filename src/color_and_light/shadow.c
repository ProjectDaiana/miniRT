#include "minirt.h"

static t_ray	create_shadow_ray(t_tuple point, t_light *light)
{
	t_tuple	direction;
	t_tuple	normalized_direction;

	direction = tuple_subtract(light->position, point);
	normalized_direction = tuple_normalize(direction);
	return (create_ray(tuple_add(point, tuple_multiply(normalized_direction,
					EPSILON)), normalized_direction));
}

int	is_shadowed(t_scene *scene, t_tuple point, t_light *light)
{
	t_ray			shadow_ray;
	t_intersections	intersections;
	double			distance;
	int				i;

	shadow_ray = create_shadow_ray(point, light);
	distance = tuple_magnitude(tuple_subtract(light->position, point));
	intersections = intersect_world(scene, shadow_ray);
	// Add distance-based attenuation
	i = 0;
	while (i < intersections.count)
	{
		if (intersections.t[i] > 0 && intersections.t[i] < distance)
			return (1);
		i++;
	}
	return (0);
}
