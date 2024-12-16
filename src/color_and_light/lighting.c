#include "minirt.h"

t_color	lighting(t_material material, t_light light, t_tuple point,
		t_tuple eye_v, t_tuple normal_v, int in_shadow)
{
	t_color color;
	
	if (material.pattern.type == CHECKERS)
		color = pattern_at(material.pattern, point);
	else
		color = material.color;
	
	t_color effective_color = color_multiply_colors(color, light.color);
	t_tuple lightv = tuple_normalize(tuple_subtract(light.position, point));
	t_color ambient = color_multiply(effective_color, material.ambient * light.intensity);

	if (in_shadow)
		return (ambient);

	double light_dot_normal = tuple_dot(lightv, normal_v);
	t_color diffuse = create_color(0, 0, 0);
	t_color specular = create_color(0, 0, 0);

	if (light_dot_normal > 0)
	{
		diffuse = color_multiply(effective_color, 
			material.diffuse * light_dot_normal * light.intensity);
		t_tuple reflectv = tuple_reflect(tuple_negate(lightv), normal_v);
		double reflect_dot_eye = tuple_dot(reflectv, eye_v);

		if (reflect_dot_eye > 0)
		{
			double factor = pow(reflect_dot_eye, material.shininess);
			specular = color_multiply(light.color, 
				material.specular * factor * light.intensity);
		}
	}
	return (color_add(color_add(ambient, diffuse), specular));
}

