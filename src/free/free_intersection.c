/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:49:27 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/29 23:45:25 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_intersections(t_intersections *xs)
{
	if (!xs)
		return ;
	if (xs->t)
	{
		free(xs->t);
		xs->t = NULL;
	}
	if (xs->object)
	{
		free(xs->object);
		xs->object = NULL;
	}
	xs->count = 0;
}

void	cleanup_camera(t_camera *camera)
{
	if (camera->transform.m)
	{
		free_mtrx(&camera->transform);
		camera->transform.m = NULL;
	}
}
