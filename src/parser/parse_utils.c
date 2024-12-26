/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:53:33 by tbella-n          #+#    #+#             */
/*   Updated: 2024/12/26 21:27:28 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_params(char **split, int count, char *element)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	if (i < count)
	{
		fprintf(stderr, "Error: Invalid %s format\n", element);
		return (0);
	}
	return (1);
}

int	validate_coordinates(char **coords, char *element, char **to_free)
{
	if (!coords || !coords[0] || !coords[1] || !coords[2])
	{
		fprintf(stderr, "Error: Invalid %s position format\n", element);
		ft_free_split(to_free);
		exit (0);
	}
	return (1);
}

int	is_valid_line(char *line)
{
	return (line[0] != '\n' && line[0] != '#' && line[0] != '\0'
		&& line[0] != ' ');
}
