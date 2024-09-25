// #include "minirt.h"

// t_color	stripe_at(t_pattern *pattern, t_tuple point)
// {
// 	if ((int)floor(point.x) % 2 == 0)
// 		return (pattern->a);
// 	else
// 		return (pattern->b);
// }

// t_pattern	create_stripe_pattern(t_color a, t_color b)
// {
// 	t_pattern	pattern;

// 	pattern.a = a;
// 	pattern.b = b;
// 	pattern.pattern_at = stripe_at;
// 	pattern.transform = create_identity_matrix();
// 	return (pattern);
// }

// t_color	checkers_at(t_pattern *pattern, t_tuple point)
// {
// 	if (((int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z))
// 		% 2 == 0)
// 		return (pattern->a);
// 	else
// 		return (pattern->b);
// }

// t_pattern	create_checkers_pattern(t_color a, t_color b)
// {
// 	t_pattern	pattern;

// 	pattern.a = a;
// 	pattern.b = b;
// 	pattern.pattern_at = checkers_at;
// 	pattern.transform = create_identity_matrix();
// 	return (pattern);
// }

// t_color	pattern_at_shape(t_pattern *pattern, void *shape, t_tuple world_point)
// {
// 	t_matrix	shape_inv_transform;
// 	t_tuple		object_point;
// 	t_tuple		pattern_point;

// 	shape_inv_transform = inverse_matrix(&((t_sphere *)shape)->transform);
// 	object_point = matrix_multiply_tuple(shape_inv_transform, world_point);
// 	pattern_point = matrix_multiply_tuple(inverse_matrix(&pattern->transform),
// 			object_point);
// 	return (pattern->pattern_at(pattern, pattern_point));
// }
