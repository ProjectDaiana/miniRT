/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:48:58 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/21 19:58:28 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_data *data)
{
	free_mtrx(&data->scene.camera.transform);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}

// int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		mlx_destroy_display(data->mlx_ptr);
// 		free(data->mlx_ptr);
// 		exit(0);
// 	}
// 	printf("Keypress: %d\n", keysym);
// 	return (0);
// }

int	handle_keyrelease(int keysym, void *data)
{
	(void)data;
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

void reset_cam_position(t_data *data)
{
	data->scene.camera.position = create_point(0, 0, -10);
	data->scene.camera.orientation = create_vector(0, 0, 1);
	data->scene.camera.up = create_vector(0, 1, 0);
	data->scene.camera.right = create_vector(1, 0, 0);
	printf(MAG"RESET position: %f, %f, %f\n"RESET, data->scene.camera.position.x, data->scene.camera.position.y, data->scene.camera.position.z);
	free_mtrx(&data->scene.camera.transform);
	render(data);
}

void rotate_camera(t_data *data, t_tuple vector)
{
	t_matrix rotation_matrix;
	t_tuple new_orientation;
	t_tuple new_up;
	t_tuple new_right;
	t_tuple new_position;
	t_tuple cam_look_at;
	t_tuple up;

	rotation_matrix = create_matrix(4);
	if (vector.x == 1)
		rotation_matrix = rotation_x(0.1);
	else if (vector.x == -1)
		rotation_matrix = rotation_x(-0.1);
	else if (vector.y == 1)
		rotation_matrix = rotation_y(0.1);
	else if (vector.y == -1)
		rotation_matrix = rotation_y(-0.1);
	new_orientation =  multiply_matrix_by_tuple(rotation_matrix, data->scene.camera.orientation);
	new_up = multiply_matrix_by_tuple(rotation_matrix, data->scene.camera.up);
	new_right =  multiply_matrix_by_tuple(rotation_matrix, data->scene.camera.right);
	new_position =  multiply_matrix_by_tuple(rotation_matrix, data->scene.camera.position);
	data->scene.camera.orientation = new_orientation;
	data->scene.camera.up = new_up;
	data->scene.camera.right = new_right;
	data->scene.camera.position = new_position;
	cam_look_at = tuple_add(data->scene.camera.position,data->scene.camera.orientation);
	up = create_vector(0, 1, 0);
	free_mtrx(&data->scene.camera.transform);
	free_mtrx(&rotation_matrix);
	data->scene.camera.transform = look_at(data->scene.camera.position, cam_look_at, up);
	render(data);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	else if (keysym == XK_Up)
		rotate_camera(data, create_vector(1, 0, 0));
	else if (keysym == XK_Down)
		rotate_camera(data, create_vector(-1, 0, 0));
	else if (keysym == XK_Left)
		rotate_camera(data, create_vector(0, -1, 0));
	else if (keysym == XK_Right)
		rotate_camera(data, create_vector(0, 1, 0));
	else if(keysym == XK_r)
	 	reset_cam_position(data);
	return (0);
}