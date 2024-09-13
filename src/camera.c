#include "minirt.h"

t_ray	create_camera_ray(t_camera camera, int x, int y)
{
	double		u;
	double		v;
	t_vector	direction;

	u = (double)x / (W_WIDTH - 1);
	v = (double)(W_HEIGHT - 1 - y) / (W_HEIGHT - 1);
	direction = normalize_vect(vect_subtraction(vect_addition(vect_addition(camera.lower_left_corner,
						vect_multiplication(camera.horizontal, u)),
					vect_multiplication(camera.vertical, v)), camera.origin));
	return (create_ray(camera.origin, direction));
}

void	setup_camera(t_camera *camera, t_vector lookfrom, t_vector lookat,
		t_vector vup, double vfov, double aspect_ratio)
{
	double		theta;
	double		half_height;
	double		half_width;
	t_vector	w;
	t_vector	u;
	t_vector	v;

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
