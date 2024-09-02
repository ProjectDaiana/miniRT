#include "minirt.h"

int	render_frame(t_data *data)
{
	int		x;
	int		y;
	Ray		ray;
	t_color	color;

	// Iterate over each pixel in the canvas
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			// Create a ray for this pixel
			ray = create_ray((double)x / W_WIDTH, (double)y / W_HEIGHT);
			// Trace the ray and get the color for this pixel
			color = trace_ray(ray, &data->scene);
			// Set the color of this pixel on our canvas
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y,
				rgb_to_int(color));
			x++;
		}
		y++;
	}
	return (0);
}
