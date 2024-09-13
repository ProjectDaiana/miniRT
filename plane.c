#include "minirt.h"

t_hit	intersect_plane(t_ray ray, t_plane plane)
{
	t_hit hit;
	double denom = dot_product(plane.normal, ray.direction);

	hit.hit = 0;
	if (fabs(denom) > 1e-6)
	{
		t_vector p0l0 = vect_subtraction(plane.point, ray.origin);
		hit.t = dot_product(p0l0, plane.normal) / denom;
		if (hit.t >= 0)
		{
			hit.hit = 1;
			hit.point = ray_position(&ray, hit.t);
			hit.normal = plane.normal;
			hit.material = plane.material;
		}
	}
	return (hit);
}
