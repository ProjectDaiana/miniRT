#include "minirt.h"

t_world	create_world(void)
{
	t_world	world;

	world.spheres = NULL;
	world.cylinders = NULL;
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


t_color	shade_hit(t_scene *scene, t_compu comps)
{
	t_color	color;
	int		in_shadow;

	color = create_color(0, 0, 0);
	for (int i = 0; i < scene->light_count; i++)
	{
		in_shadow = is_shadowed(scene, comps.over_point, &scene->lights[i]);
		color = color_add(color, lighting(((t_cylinder *)comps.object)->material,
					scene->lights[i], comps.point, comps.eyev, comps.normalv,
					in_shadow));
	}
	return (color);
}

t_color	color_at(t_scene *scene, t_ray ray)
{
	t_intersections	xs;
	t_compu			comps;

	xs = intersect_world(scene, ray);
	if (xs.count == 0)
	{
		return (create_color(0, 0, 0));
	}
	comps = prepare_computations(xs.t[0], ray, &xs);
	return (shade_hit(scene, comps));
}
