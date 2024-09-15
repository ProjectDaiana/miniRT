#include "minirt.h"

t_ray	create_camera_ray(t_camera camera, int x, int y)
{
	double		u;
	double		v;
	t_tuple	direction;

	u = (double)x / (W_WIDTH - 1);
	v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
	printf(MAG"u %f"RESET, u);
	printf(MAG"v %f"RESET, v);
	direction = normalize_vect(vect_subtraction(vect_addition(vect_addition(camera.lower_left_corner,
						vect_multiplication(camera.horizontal, u)),
					vect_multiplication(camera.vertical, v)), camera.origin));
	// direction.x = 1.0;
	// direction.y = 2.0;
	// direction.z = 3.0;
	// direction.w = 0;
	//printf(MAG"create camera ray direction %f %f %f %f\n"RESET, direction.z, direction.y, direction.z, direction.w);
	//printf(MAG"create camera ray origin %f %f %f %f\n"RESET, camera.origin.x, camera.origin.y, camera.origin.z, camera.origin.w);
	return (create_ray(camera.origin, direction));
}

void	setup_camera(t_camera *camera, t_tuple lookfrom, t_tuple lookat,
		t_tuple vup, double vfov, double aspect_ratio)
{
	double		theta;
	double		half_height;
	double		half_width;
	t_tuple	w;
	t_tuple	u;
	t_tuple	v;

	theta = vfov * M_PI / 180;
	half_height = tan(theta / 2);
	half_width = aspect_ratio * half_height;
	camera->origin = lookfrom;
	w = normalize_vect(vect_subtraction(lookfrom, lookat));
	u = normalize_vect(cross_product(vup, w));
	v = cross_product(w, u);
	camera->lower_left_corner = vect_subtraction(vect_subtraction(vect_subtraction(camera->origin,
					vect_multiplication(u, half_width)), vect_multiplication(v,
					half_height)), w);
	camera->horizontal = vect_multiplication(u, 2 * half_width);
	camera->vertical = vect_multiplication(v, 2 * half_height);
}
