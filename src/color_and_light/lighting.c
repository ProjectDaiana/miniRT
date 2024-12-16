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
	effective_color = color_multiply(effective_color, light.intensity);
	
	if (in_shadow)
		return color_multiply(effective_color, material.ambient);

	t_tuple lightv = tuple_normalize(tuple_subtract(light.position, point));
	double light_dot_normal = tuple_dot(lightv, normal_v);
	
	if (light_dot_normal < 0)
		return color_multiply(effective_color, material.ambient);
		
	t_color diffuse = color_multiply(effective_color, 
		material.diffuse * light_dot_normal);
		
	t_tuple reflectv = tuple_reflect(tuple_negate(lightv), normal_v);
	double reflect_dot_eye = tuple_dot(reflectv, eye_v);
	t_color specular = create_color(0, 0, 0);
	
	if (reflect_dot_eye > 0)
	{
		double factor = pow(reflect_dot_eye, material.shininess);
		specular = color_multiply(light.color, 
			material.specular * factor * light.intensity);
	}
	
	return color_add(color_add(
		color_multiply(effective_color, material.ambient),
		diffuse),
		specular);
}

