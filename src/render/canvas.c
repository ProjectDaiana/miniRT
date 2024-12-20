/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:11:14 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:11:18 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_canvas_row(t_color *row, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		row[j] = create_color(0, 0, 0);
		j++;
	}
}

t_canvas	create_canvas(int width, int height)
{
	t_canvas	canvas;
	int			i;

	canvas.width = width;
	canvas.height = height;
	canvas.pixels = (t_color **)malloc(sizeof(t_color *) * height);
	i = 0;
	while (i < height)
	{
		canvas.pixels[i] = (t_color *)malloc(sizeof(t_color) * width);
		init_canvas_row(canvas.pixels[i], width);
		i++;
	}
	return (canvas);
}

static void	write_row_to_ppm(FILE *file, t_canvas *canvas, int y)
{
	int		x;
	t_color	color;

	x = 0;
	while (x < canvas->width)
	{
		color = canvas->pixels[y][x];
		fprintf(file, "%d %d %d ", (int)(color.r * 255), (int)(color.g * 255),
			(int)(color.b * 255));
		x++;
	}
	fprintf(file, "\n");
}

void	canvas_to_ppm(t_canvas *canvas, const char *filename)
{
	FILE	*file;
	int		y;

	file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file for writing\n");
		return ;
	}
	y = 0;
	while (y < canvas->height)
	{
		write_row_to_ppm(file, canvas, y);
		y++;
	}
	fclose(file);
}
