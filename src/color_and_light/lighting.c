#include "minirt.h"

static t_light_data	init_light_data(t_lighting_params params)
{
	t_light_data	data;

	data.material = params.material;
	data.light = params.light;
	data.point = params.point;
	data.eye_v = params.eye_v;
	data.normal_v = params.normal_v;
	data.in_shadow = params.in_shadow;
	return (data);
}

static t_color	get_diffuse_and_specular(t_lighting_params params,
		t_tuple lightv, t_color base_color)
{
	t_light_data	data;
	t_color			diffuse;
	t_color			specular;
	t_tuple			reflectv;
	double			dot;

	data = init_light_data(params);
	dot = fmax(tuple_dot(lightv, params.normal_v), 0.0);
	diffuse = get_diffuse_component(base_color, &data, dot);
	reflectv = tuple_reflect(tuple_negate(lightv), params.normal_v);
	dot = fmax(tuple_dot(reflectv, params.eye_v), 0.0);
	specular = get_specular_component(&data, dot);
	return (color_add(diffuse, specular));
}

t_color	lighting(t_lighting_params params)
{
	t_light_data	data;
	t_color			base_color;
	t_color			ambient;
	t_tuple			lightv;
	t_color			final;

	// printf("DEBUG: Material color before lighting: R=%d, G=%d, B=%d\n",
	// 	params.material.color.r, params.material.color.g,
	// 	params.material.color.b);
	data = init_light_data(params);
	base_color = get_base_color(params.material, params.point);
	// printf("DEBUG: Base color after get_base_color: R=%d, G=%d, B=%d\n",
	// 	base_color.r, base_color.g, base_color.b);
	ambient = get_ambient_component(base_color, &data);
	// printf("DEBUG: Ambient component: R=%d, G=%d, B=%d\n", 
	// 	ambient.r, ambient.g, ambient.b);
	
	if (params.in_shadow)
	{
		// printf("DEBUG: Object is in shadow\n");
		return (ambient);
	}

	lightv = tuple_normalize(tuple_subtract(params.light.position,
				params.point));
	final = color_add(ambient, get_diffuse_and_specular(params, lightv,
				base_color));
	// printf("DEBUG: Final color: R=%d, G=%d, B=%d\n", final.r, final.g, final.b);
	return (final);
}
