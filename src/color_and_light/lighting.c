#include "minirt.h"

// t_color	calculate_lighting(t_hit hit, t_scene *scene, t_ray ray)
// {
// 	t_color ambient, diffuse, specular, result;
// 	t_vector light_dir, view_dir, reflect_dir;
// 	double diff, spec;

// 	ambient = multiply_color_by_scalar(scene->ambient_color,
// 			scene->ambient_intensity);

// 	light_dir = vect_normalize(vect_subtraction(scene->light.position,
// 				hit.point));

// 	// Diffuse
// 	diff = fmax(dot_product(hit.normal, light_dir), 0.0);
// 	diffuse = multiply_color_by_scalar(scene->light.color, diff
// 			* scene->sphere.material.diffuse);

// 	// Specular
// 	view_dir = vect_normalize(vect_negate(ray.direction));
// 	reflect_dir = vect_reflect(vect_negate(light_dir), hit.normal);
// 	spec = pow(fmax(dot_product(view_dir, reflect_dir), 0.0),
// 			scene->sphere.material.shininess);
// 	specular = multiply_color_by_scalar(scene->light.color, spec
// 			* scene->sphere.material.specular);

// 	result = add_color(ambient, add_color(diffuse, specular));
// 	return (color_multiply(result, scene->sphere.material.color));
// }

t_color	calculate_lighting(t_hit hit, t_scene *scene, t_ray ray)
{
	t_color ambient, diffuse, result;
	t_vector light_dir;
	double diff;
	(void)ray;

	ambient = multiply_color_by_scalar(&scene->ambient_color,
			scene->ambient_intensity);

	light_dir = normalize_vect(vect_subtraction(scene->light.position,
				hit.point));

	// Diffuse
	diff = fmax(dot_product(hit.normal, light_dir), 0.0);
	diffuse = multiply_color_by_scalar(&scene->light.color, diff
			* hit.material.diffuse);

	result = add_color(ambient, diffuse);
	return (color_multiply(result, hit.material.color));
}