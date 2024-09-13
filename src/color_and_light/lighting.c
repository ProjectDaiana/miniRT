#include "minirt.h"

// t_color	calculate_lighting(t_hit hit, t_scene *scene, t_ray ray)
// {
// 	t_color ambient, diffuse, result;
// 	t_vector light_dir;
// 	double diff;
// 	(void)ray;

// 	ambient = multiply_color_by_scalar(&scene->ambient_color,
// 			scene->ambient_intensity);

// 	light_dir = normalize_vect(vect_subtraction(scene->light.position,
// 				hit.point));

// 	// Diffuse
// 	diff = fmax(dot_product(hit.normal, light_dir), 0.0);
// 	diffuse = multiply_color_by_scalar(&scene->light.color, diff
// 			* hit.material.diffuse);

// 	result = add_color(ambient, diffuse);
// 	return (color_multiply(result, hit.material.color));
// }

t_color	calculate_lighting(t_hit hit, t_scene *scene, t_ray ray)
{
	t_color ambient, diffuse, specular, result;
	t_vector light_dir, reflect_dir;
	double diff, spec;

	ambient = multiply_color_by_scalar(&scene->ambient_color,
			scene->ambient_intensity);

	light_dir = normalize_vect(vect_subtraction(scene->light.position,
				hit.point));

	// Diffuse
	diff = fmax(dot_product(hit.normal, light_dir), 0.0);
	diffuse = multiply_color_by_scalar(&scene->light.color, diff
			* hit.material.diffuse);

	// Specular
	reflect_dir = reflect(vect_multiplication(light_dir, -1), hit.normal);
	spec = pow(fmax(dot_product(reflect_dir, vect_multiplication(ray.direction,
						-1)), 0.0), hit.material.shininess);
	specular = multiply_color_by_scalar(&scene->light.color, spec
			* hit.material.specular);

	result = add_color(add_color(ambient, diffuse), specular);
	return (color_multiply(result, hit.material.color));
}