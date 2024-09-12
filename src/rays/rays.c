#include "minirt.h"

t_ray ray(t_tuple *origin, t_tuple *direction)
{
	t_ray ray;

	ray.origin = *origin;
	ray.direction = *direction;
	return (ray);
}


t_tuple position(t_tuple *origin, t_tuple *direction, double t)
{
	t_tuple ray;

	ray.x = origin->x + t * direction->x;
	ray.y = origin->y + t * direction->y;
	ray.z = origin->z + t * direction->z;
	ray.w = 1;
	printf("Ray: %f, %f, %f, %f\n", ray.x, ray.y, ray.z, ray.w);
	
	return (ray);
}

t_intersections intersect(t_sphere s, t_ray r) {
    // Calculate the vector from the sphere's center to the ray origin
    t_tuple sphere_to_ray = {r.origin.x - s.center.x, r.origin.y - s.center.y, r.origin.z - s.center.z , 1};

    // Compute the quadratic equation components
    double a = pow(r.direction.x, 2) + pow(r.direction.y, 2) + pow(r.direction.z, 2);
    double b = 2 * (sphere_to_ray.x * r.direction.x + sphere_to_ray.y * r.direction.y + sphere_to_ray.z * r.direction.z);
    double c = pow(sphere_to_ray.x, 2) + pow(sphere_to_ray.y, 2) + pow(sphere_to_ray.z, 2) - pow(s.radius, 2);

    // Discriminant
    double discriminant = pow(b, 2) - 4 * a * c;

    t_intersections xs;
    if (discriminant < 0) {
        // No intersection
        xs.t1 = -1;
        xs.t2 = -1;
    } else {
        xs.t1 = (-b - sqrt(discriminant)) / (2 * a);
        xs.t2 = (-b + sqrt(discriminant)) / (2 * a);
    }
    return xs;
}

t_tuple point(double x, double y, double z, double w) {
    return (t_tuple){x, y, z, w};
}


t_sphere sphere()
{
    t_sphere s = {
		.center = {0, 0, 0, 1},
		.radius = 1
	};
    return s;
}