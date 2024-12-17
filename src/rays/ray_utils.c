#include "minirt.h"

t_material	get_object_material(void *object)
{
	if (((t_sphere *)object)->radius > 0)
		return (((t_sphere *)object)->material);
	return (((t_plane *)object)->material);
}

t_tuple	get_object_normal(void *object, t_tuple point)
{
	return (normal_at(object, point));
}

t_color	get_reflection_color(t_scene *scene, t_ray reflect_ray,
		void *reflect_object, t_tuple reflect_point)
{
	t_material			reflect_material;
	t_tuple				reflect_normal;
	t_tuple				reflect_eye;
	int					in_shadow;
	t_lighting_params	params;

	reflect_material = get_object_material(reflect_object);
	reflect_normal = get_object_normal(reflect_object, reflect_point);
	reflect_eye = tuple_negate(reflect_ray.direction);
	in_shadow = is_shadowed(scene, reflect_point, &scene->light);
	params = (t_lighting_params){reflect_material, scene->light, reflect_point,
		reflect_eye, reflect_normal, in_shadow};
	return (lighting(params));
}

t_color	get_surface_color(t_scene *scene, t_material material, t_compu comps)
{
	int					in_shadow;
	t_lighting_params	params;

	in_shadow = is_shadowed(scene, comps.point, &scene->light);
	params = (t_lighting_params){material, scene->light, comps.point,
		comps.eyev, comps.normalv, in_shadow};
	return (lighting(params));
}

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
