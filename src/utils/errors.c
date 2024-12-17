#include "minirt.h"

void	print_error(char *msg)
{
	printf(RED "%s\n" RESET, msg);
	exit(EXIT_FAILURE);
}
