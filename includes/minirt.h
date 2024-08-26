# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/libft/libft.h"

#define  W_WIDTH 1200
#define  W_HEIGHT 800
#define  MLX_ERROR 1

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

typedef struct vector
{
	double x;
	double y;
	double z;
} t_vector;

typedef struct scene
{

} t_scene;

typedef struct data
{
	void *mlx_ptr;
	void *win_ptr;
} t_data;

int	handle_no_event(void *data);
int	handle_keypress(int keysym, t_data *data);
int	handle_keyrelease(int keysym, void *data);