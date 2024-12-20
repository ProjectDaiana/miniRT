#include "minirt.h"

static int	is_cylinder(void *object)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)object;
	return (cylinder->diameter > 0 && 
		cylinder->height > 0 && 
		cylinder->axis.w == 0 && // Must be a vector
		cylinder->center.w == 1.0 && // Must be a point
		fabs(tuple_magnitude(cylinder->axis) - 1.0) < EPSILON); // Normalized axis
}

static int	is_sphere(void *object)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object;
	return (sphere->radius > 0 && 
		sphere->center.w == 1.0 && // Must be a point
		sphere->material.color.r >= 0 && 
		sphere->material.color.g >= 0 && 
		sphere->material.color.b >= 0);
}

static int	is_plane(void *object)
{
	t_plane	*plane;

	plane = (t_plane *)object;
	// Basic structural checks
	if (!plane || plane->point.w != 1.0 || plane->normal.w != 0.0)
		return (0);
	
	// Check if it has a valid normal vector (not zero)
	if (!(plane->normal.x != 0 || plane->normal.y != 0 || plane->normal.z != 0))
		return (0);
        
	// Debug output to track plane properties
	// printf("DEBUG Plane check:\n");
	// printf("Point: (%f, %f, %f, %f)\n", 
	// 	plane->point.x, plane->point.y, plane->point.z, plane->point.w);
	// printf("Normal: (%f, %f, %f, %f)\n", 
	// 	plane->normal.x, plane->normal.y, plane->normal.z, plane->normal.w);
	// printf("Color: (%d, %d, %d)\n", 
	// 	plane->material.color.r, plane->material.color.g, plane->material.color.b);

	return (1);
}

t_material	get_object_material(void *object)
{
	if (!object)
	{
		// printf("DEBUG: NULL object passed to get_object_material\n");
		return ((t_material){0}); // Return empty material for NULL
	}
	
	if (is_sphere(object))
		return (((t_sphere *)object)->material);
	if (is_cylinder(object))
		return (((t_cylinder *)object)->material);
	if (is_plane(object))
	{
		// printf("DEBUG: Plane material found with color: R=%d, G=%d, B=%d\n",
			// ((t_plane *)object)->material.color.r,
			// ((t_plane *)object)->material.color.g,
			// ((t_plane *)object)->material.color.b);
		return (((t_plane *)object)->material);
	}

	// printf("DEBUG: ERROR object type not identified\n");
	return ((t_material){0}); // Return empty material as fallback
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
