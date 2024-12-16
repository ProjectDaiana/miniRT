#include "minirt.h"

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	position(t_ray ray, double t)
{
	return (tuple_add(ray.origin, tuple_multiply(ray.direction, t)));
}

// ok

// t_color	ray_color(t_scene *scene, t_ray ray)
// {
// 	t_intersections	xs;
// 	t_tuple			point;
// 	t_tuple			normal;
// 	t_tuple			eye;
// 	int				in_shadow;
// 	t_material		material;
// 	void			*object;

// 	xs = intersect_world(scene, ray);
// 	if (xs.count > 0)
// 	{
// 		point = position(ray, xs.t[0]);
// 		object = xs.object[0];
// 		if (((t_sphere *)object)->radius > 0) // It's a sphere
// 		{
// 			normal = normal_at(object, point);
// 			material = ((t_sphere *)object)->material;
// 		}
// 		else // It's a plane
// 		{
// 			normal = normal_at(object, point);
// 			material = ((t_plane *)object)->material;
// 		}
// 		eye = tuple_negate(ray.direction);
// 		in_shadow = is_shadowed(scene, point, &scene->light);
// 		return (lighting(material, scene->light, point, eye, normal,
// 				in_shadow));
// 	}
// 	return (create_color(0, 0, 0));
// }

t_color	ray_color(t_scene *scene, t_ray ray)
{
	t_intersections xs;
	t_tuple point;
	t_tuple normal;
	t_tuple eye;
	int in_shadow;
	t_material material;
	void *object;

	xs = intersect_world(scene, ray);
	if (xs.count > 0)
	{
		point = position(ray, xs.t[0]);
		object = xs.object[0];
		if (((t_sphere *)object)->radius > 0) // It's a sphere
		{
			normal = normal_at(object, point);
			material = ((t_sphere *)object)->material;
		}
		else // It's a plane
		{
			normal = normal_at(object, point);
			material = ((t_plane *)object)->material;
		}
		eye = tuple_negate(ray.direction);

		// Calculate reflection
		t_tuple reflect_dir = tuple_reflect(ray.direction, normal);
		t_ray reflect_ray = create_ray(point, reflect_dir);
		t_color reflect_color = create_color(0, 0, 0);

		// Only calculate reflection if reflectivity > 0
		if (material.reflective > 0)
		{
			t_intersections reflect_xs = intersect_world(scene, reflect_ray);
			if (reflect_xs.count > 0)
			{
				t_tuple reflect_point = position(reflect_ray, reflect_xs.t[0]);
				t_tuple reflect_normal;
				t_material reflect_material;
				void *reflect_object = reflect_xs.object[0];

				if (((t_sphere *)reflect_object)->radius > 0)
				{
					reflect_normal = normal_at(reflect_object, reflect_point);
					reflect_material = ((t_sphere *)reflect_object)->material;
				}
				else
				{
					reflect_normal = normal_at(reflect_object, reflect_point);
					reflect_material = ((t_plane *)reflect_object)->material;
				}

				t_tuple reflect_eye = tuple_negate(reflect_ray.direction);
				in_shadow = is_shadowed(scene, reflect_point, &scene->light);
				reflect_color = lighting(reflect_material, scene->light,
						reflect_point, reflect_eye, reflect_normal, in_shadow);
			}
		}

		in_shadow = is_shadowed(scene, point, &scene->light);
		t_color surface_color = lighting(material, scene->light, point, eye,
				normal, in_shadow);

		// Blend surface and reflection colors
		return (color_add(color_multiply(surface_color, 1.0
					- material.reflective), color_multiply(reflect_color,
					material.reflective)));
	}
	return (create_color(0, 0, 0));
}
