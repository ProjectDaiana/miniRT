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
		return (0);
	}
	return (1);
}

void	free_splits(char **split1, char **split2, char **split3)
{
	if (split1)
		ft_free_split(split1);
	if (split2)
		ft_free_split(split2);
	if (split3)
		ft_free_split(split3);
}

int	is_valid_line(char *line)
{
	return (line[0] != '\n' && line[0] != '#' && line[0] != '\0'
		&& line[0] != ' ');
}
