#include "minirt.h"

t_world	create_world(void)
{
	t_world	world;

	world.spheres = NULL;
	world.lights = NULL;
	return (world);
}

t_color	color_at(t_scene *scene, t_ray ray, int remaining)
{
	t_intersections	xs;
	t_compu			comps;

	if (remaining <= 0) // Add explicit check
		return (create_color(0, 0, 0));
	xs = intersect_world(scene, ray);
	if (xs.count == 0)
		return (create_color(0, 0, 0));
	comps = prepare_computations(xs.t[0], ray, &xs);
	return (shade_hit(scene, comps, remaining));
}

t_color	reflected_color(t_scene *scene, t_compu comps, int remaining)
{
	double	reflective;
	t_ray	reflect_ray;
	t_color	color;

	if (remaining <= 0)
		return (create_color(0, 0, 0));
	
	t_material material = get_object_material(comps.object);
	reflective = material.reflective;
	
	if (reflective < EPSILON)
		return (create_color(0, 0, 0));
	reflect_ray = create_ray(comps.over_point, comps.reflectv);
	color = color_at(scene, reflect_ray, remaining - 1);
	return (color_multiply(color, reflective));
}



t_color	shade_hit(t_scene *scene, t_compu comps, int remaining)
{
	t_material			material;
	t_color				surface;
	t_color				reflected;
	int					shadowed;
	t_lighting_params	params;

	material = get_object_material(comps.object);
	shadowed = is_shadowed(scene, comps.over_point, &scene->light);
	params.material = material;
	params.light = scene->light;
	params.point = comps.point;
	params.eye_v = comps.eyev;
	params.normal_v = comps.normalv;
	params.in_shadow = shadowed;
	surface = lighting(params);
	reflected = reflected_color(scene, comps, remaining);
	return (color_add(surface, reflected));
}

double	schlick(t_compu comps)
{
	double	cos;
	double	n;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos = tuple_dot(comps.eyev, comps.normalv);
	if (comps.n1 > comps.n2)
	{
		n = comps.n1 / comps.n2;
		sin2_t = n * n * (1.0 - cos * cos);
		if (sin2_t > 1.0)
			return (1.0);
		cos_t = sqrt(1.0 - sin2_t);
		cos = cos_t;
	}
	r0 = pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);
	return (r0 + (1 - r0) * pow(1 - cos, 5));
}
