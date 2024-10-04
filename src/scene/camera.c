#include "minirt.h"

t_camera	create_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	cam;

	double half_view, aspect;
	cam.height = hsize;
	cam.width = vsize;
	cam.fov = field_of_view;
	cam.transform = create_identity_matrix();
	print_matrix(cam.transform, "Camera Transform", 4);
	half_view = tan(field_of_view / 2);
	aspect = (double)hsize / vsize;
	if (aspect >= 1)
	{
		cam.half_width = half_view;
		cam.half_height = half_view / aspect;
	}
	else
	{
		cam.half_width = half_view * aspect;
		cam.half_height = half_view;
	}
	cam.pixel_size = (cam.half_width * 2) / hsize;
	return (cam);
}

t_ray	ray_for_pixel(t_camera *cam, int px, int py)
{
	double xoffset = (px + 0.5) * cam->pixel_size;
	double yoffset = (py + 0.5) * cam->pixel_size;

	double world_x = cam->half_width - xoffset;
	double world_y = cam->half_height - yoffset;

	t_matrix inv_transform = inverse_matrix(&cam->transform);
	t_tuple pixel = matrix_multiply_tuple(inv_transform, create_point(world_x,
				world_y, -1));
	t_tuple origin = matrix_multiply_tuple(inv_transform, create_point(0, 0,
				0));
	t_tuple direction = tuple_normalize(tuple_subtract(pixel, origin));

	return (create_ray(origin, direction));
}
