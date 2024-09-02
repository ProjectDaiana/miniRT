#include "minirt.h"

t_color	calculate_lighting(t_hit hit, t_scene *scene, Ray ray)
{
	t_color ambient;
	t_color diffuse;
	t_color specular;
	t_vector light_dir;
	double light_distance;
	Ray shadow_ray;
	t_hit shadow_hit;
	double diff;
	t_vector view_dir;
	t_vector reflect_dir;
	double spec;
	t_color result;

	ambient = multiply_color_by_scalar(scene->ambient_color,
			scene->ambient_intensity);
	diffuse = (t_color){0, 0, 0};
	specular = (t_color){0, 0, 0};
	light_dir = vect_normalize(vect_subtraction(scene->light.position,
				hit.point));
	light_distance = vect_length(vect_subtraction(scene->light.position,
				hit.point));
	shadow_ray.origin = hit.point;
	shadow_ray.direction = light_dir;
	shadow_hit = intersect_sphere(shadow_ray, scene->sphere);
	if (!shadow_hit.hit || shadow_hit.t > light_distance)
	{
		diff = fmax(dot_product(hit.normal, light_dir), 0.0);
		diffuse = multiply_color_by_scalar(scene->light.color, diff
				* scene->sphere.material.diffuse);
		view_dir = vect_normalize(vect_negate(ray.direction));
		reflect_dir = vect_reflect(vect_negate(light_dir), hit.normal);
		spec = pow(fmax(dot_product(view_dir, reflect_dir), 0.0),
				scene->sphere.material.shininess);
		specular = multiply_color_by_scalar(scene->light.color, spec
				* scene->sphere.material.specular);
	}
	result = add_color(ambient, add_color(diffuse, specular));
	return (color_multiply(result, scene->sphere.material.color));
}
