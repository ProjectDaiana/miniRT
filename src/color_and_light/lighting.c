#include "minirt.h"

// t_color	lighting(t_material material, t_light light, t_tuple point,
// 		t_tuple eye_v, t_tuple normal_v, int in_shadow)
// {
// 	t_color effective_color = color_multiply_colors(material.color,
// 			light.color);
// 	t_tuple light_v = tuple_normalize(tuple_subtract(light.position, point));
// 	t_color ambient = color_multiply(effective_color, material.ambient);

// 	if (in_shadow)
// 		return (ambient);

// 	double light_dot_normal = tuple_dot(light_v, normal_v);
// 	t_color diffuse, specular;

// 	if (light_dot_normal < 0)
// 	{
// 		diffuse = create_color(0, 0, 0);
// 		specular = create_color(0, 0, 0);
// 	}
// 	else
// 	{
// 		diffuse = color_multiply(effective_color, material.diffuse
// 				* light_dot_normal);
// 		t_tuple reflect_v = tuple_reflect(tuple_negate(light_v), normal_v);
// 		double reflect_dot_eye = tuple_dot(reflect_v, eye_v);

// 		if (reflect_dot_eye <= 0)
// 			specular = create_color(0, 0, 0);
// 		else
// 		{
// 			double factor = pow(reflect_dot_eye, material.shininess);
// 			specular = color_multiply(light.color, material.specular * factor);
// 		}
// 	}

// 	return (color_add(color_add(ambient, diffuse), specular));
// }


t_color	lighting(t_material material, t_light light, t_tuple point,
		t_tuple eye_v, t_tuple normal_v, int in_shadow)
{
	t_color effective_color = color_multiply_colors(material.color,
			light.color);
	t_tuple light_v = tuple_normalize(tuple_subtract(light.position, point));
	t_color ambient = color_multiply(effective_color, material.ambient);

	if (in_shadow)
		return (ambient);

	double light_dot_normal = tuple_dot(light_v, normal_v);
	t_color diffuse = create_color(0, 0, 0);
	t_color specular = create_color(0, 0, 0);

	if (light_dot_normal >= 0)
	{
		diffuse = color_multiply(effective_color, material.diffuse
				* light_dot_normal);
		t_tuple reflect_v = tuple_reflect(tuple_negate(light_v), normal_v);
		double reflect_dot_eye = tuple_dot(reflect_v, eye_v);

		if (reflect_dot_eye > 0)
		{
			double factor = pow(reflect_dot_eye, material.shininess);
			specular = color_multiply(light.color, material.specular * factor);
		}
	}

	return (color_add(color_add(ambient, diffuse), specular));
}
