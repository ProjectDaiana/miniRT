#include "minirt.h"

t_canvas	create_canvas(int width, int height)
{
	t_canvas	canvas;
	int			i;

	canvas.width = width;
	canvas.height = height;
	canvas.pixels = (t_color **)malloc(sizeof(t_color *) * height);
	for (i = 0; i < height; i++)
	{
		canvas.pixels[i] = (t_color *)malloc(sizeof(t_color) * width);
		for (int j = 0; j < width; j++)
		{
			canvas.pixels[i][j] = create_color(0, 0, 0); // Initialize to black
		}
	}
	return (canvas);
}

void	write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		canvas->pixels[y][x] = color;
	}
}

t_color	pixel_at(t_canvas *canvas, int x, int y)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		return (canvas->pixels[y][x]);
	}
	return (create_color(0, 0, 0)); // Return black for out of bounds
}

void	canvas_to_ppm(t_canvas *canvas, const char *filename)
{
	FILE	*file;
	t_color	color;

	file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file for writing\n");
		return ;
	}
	fprintf(file, "P3\n%d %d\n255\n", canvas->width, canvas->height);
	for (int y = 0; y < canvas->height; y++)
	{
		for (int x = 0; x < canvas->width; x++)
		{
			color = canvas->pixels[y][x];
			fprintf(file, "%d %d %d ", (int)(color.r * 255), (int)(color.g
					* 255), (int)(color.b * 255));
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

void	free_canvas(t_canvas *canvas)
{
	for (int i = 0; i < canvas->height; i++)
	{
		free(canvas->pixels[i]);
	}
	free(canvas->pixels);
}
