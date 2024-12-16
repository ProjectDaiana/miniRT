#include "minirt.h"

t_world	create_world(void)
{
	t_world	world;

	world.spheres = NULL;
	world.lights = NULL;
	return (world);
}

// t_color	shade_hit(t_scene *scene, t_compu comps)
// {
// 	t_color	color;
// 	int		in_shadow;

// 	color = create_color(0, 0, 0);
// 	for (int i = 0; i < scene->light_count; i++)
// 	{
// 		in_shadow = is_shadowed(scene, comps.over_point, &scene->lights[i]);
// 		color = color_add(color, lighting(((t_sphere *)comps.object)->material,
// 					scene->lights[i], comps.point, comps.eyev, comps.normalv,
// 					in_shadow));
// 	}
// 	return (color);
// }

// t_color	color_at(t_scene *scene, t_ray ray)
// {
// 	t_intersections	xs;
// 	t_compu			comps;

// 	xs = intersect_world(scene, ray);
// 	if (xs.count == 0)
// 	{
// 		return (create_color(0, 0, 0));
// 	}
// 	comps = prepare_computations(xs.t[0], ray, &xs);
// 	return (shade_hit(scene, comps));
// }

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
	double	reflective;
	t_ray	reflect_ray;
	t_color	color;

	if (remaining <= 0)
	{
		// printf("Max reflection depth reached\n");
		return (create_color(0, 0, 0));
	}
	// Get reflective value based on object type
	if (((t_sphere *)comps.object)->radius > 0)
		reflective = ((t_sphere *)comps.object)->material.reflective;
	else
		reflective = ((t_plane *)comps.object)->material.reflective;
	// printf("Calculating reflection with reflectivity: %f\n", reflective);
	if (reflective == 0)
		return (create_color(0, 0, 0));
	reflect_ray = create_ray(comps.over_point, comps.reflectv);
	color = color_at(scene, reflect_ray, remaining - 1);
	return (color_multiply(color, reflective));
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
	// printf("Surface color: R:%d G:%d B:%d\n", surface.r, surface.g, surface.b);
	// printf("Reflected color: R:%d G:%d B:%d\n", reflected.r, reflected.g,reflected.b);
	return (color_add(surface, reflected));
}
