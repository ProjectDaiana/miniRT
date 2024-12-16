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

	xs = intersect_world(scene, ray);
	if (xs.count == 0)
		return (create_color(0, 0, 0));
	comps = prepare_computations(xs.t[0], ray, &xs);
	return (shade_hit(scene, comps, remaining));
}

t_color	reflected_color(t_scene *scene, t_compu comps, int remaining)
{
	if (remaining <= 0)
		return create_color(0, 0, 0);

	if (((t_sphere *)comps.object)->radius > 0)
	{
		t_ray reflect_ray = create_ray(comps.over_point, comps.reflectv);
		t_color color = color_at(scene, reflect_ray, remaining - 1);
		
		t_material material = ((t_sphere *)comps.object)->material;
		return color_multiply(color, material.reflective * 0.5);
	}
	
	return create_color(0, 0, 0);
}

t_color	shade_hit(t_scene *scene, t_compu comps, int remaining)
{
	t_color		surface;
	t_color		reflected;
	int			shadowed;
	t_material	material;

	if (((t_sphere *)comps.object)->radius > 0)
		material = ((t_sphere *)comps.object)->material;
	else
		material = ((t_plane *)comps.object)->material;
	shadowed = is_shadowed(scene, comps.over_point, &scene->light);
	surface = lighting(material, scene->light, comps.point, comps.eyev,
			comps.normalv, shadowed);
	reflected = reflected_color(scene, comps, remaining);
	return (color_add(surface, reflected));
}
