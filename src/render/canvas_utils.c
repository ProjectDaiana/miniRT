/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbella-n <tbella-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 20:11:08 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/20 20:11:10 by tbella-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_canvas(t_canvas *canvas)
{
	int	i;

	i = 0;
	while (i < canvas->height)
	{
		free(canvas->pixels[i]);
		i++;
	}
	free(canvas->pixels);
}

t_color	pixel_at(t_canvas *canvas, int x, int y)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
		return (canvas->pixels[y][x]);
	return (create_color(0, 0, 0));
}

void	write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
		canvas->pixels[y][x] = color;
}
