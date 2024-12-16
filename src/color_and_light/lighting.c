#include "minirt.h"

t_color	lighting(t_material material, t_light light, t_tuple point,
		t_tuple eye_v, t_tuple normal_v, int in_shadow)
{
	t_color color;
	t_color ambient, diffuse, specular;
	t_tuple lightv;
	double light_dot_normal, reflect_dot_eye;
	
	// Get base color
	color = (material.pattern.type == CHECKERS) ? 
		pattern_at(material.pattern, point) : material.color;
	
	// Calculate ambient (not affected by intensity)
	ambient = color_multiply(color_multiply_colors(color, light.color), 
		material.ambient);
	
	if (in_shadow)
		return ambient;

	// Calculate diffuse and specular
	lightv = tuple_normalize(tuple_subtract(light.position, point));
	light_dot_normal = fmax(tuple_dot(lightv, normal_v), 0.0);
	
	// Diffuse calculation with smoother transition
	diffuse = color_multiply(color_multiply_colors(color, light.color),
		material.diffuse * pow(light_dot_normal, 1.1) * light.intensity);
		
	// Specular calculation with improved falloff
	t_tuple reflectv = tuple_reflect(tuple_negate(lightv), normal_v);
	reflect_dot_eye = fmax(tuple_dot(reflectv, eye_v), 0.0);
	
	if (reflect_dot_eye > 0)
	{
		double factor = pow(reflect_dot_eye, material.shininess);
		specular = color_multiply(light.color, 
			material.specular * factor * light.intensity);
	}
	else
		specular = create_color(0, 0, 0);
	
	// Blend components
	return color_add(color_add(ambient, diffuse), specular);
}

