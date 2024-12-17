#include "minirt.h"

t_camera	create_camera(int hsize, int vsize, double field_of_view)
{
	t_camera	cam;
	double		half_view;
	double		aspect;

	cam.height = hsize;
	cam.width = vsize;
	cam.fov = field_of_view;
	cam.transform = create_identity_matrix();
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

static t_tuple	get_pixel_position(t_camera *cam, int px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;

	xoffset = (px + 0.5) * cam->pixel_size;
	yoffset = (py + 0.5) * cam->pixel_size;
	world_x = cam->half_width - xoffset;
	world_y = cam->half_height - yoffset;
	return (create_point(world_x, world_y, -1));
}

static t_tuple	transform_point(t_matrix transform, t_tuple point)
{
	t_tuple	result;

	result = matrix_multiply_tuple(transform, point);
	return (result);
}

t_ray	ray_for_pixel(t_camera *cam, int px, int py)
{
	t_matrix	inv_transform;
	t_tuple		pixel;
	t_tuple		origin;
	t_tuple		direction;

	inv_transform = inverse_matrix(&cam->transform);
	pixel = transform_point(inv_transform, get_pixel_position(cam, px, py));
	origin = transform_point(inv_transform, create_point(0, 0, 0));
	direction = tuple_normalize(tuple_subtract(pixel, origin));
	return (create_ray(origin, direction));
}
