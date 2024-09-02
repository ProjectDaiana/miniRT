# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/libft/libft.h"

#define  W_WIDTH 1200
#define  W_HEIGHT 800
#define  MLX_ERROR 1
#define  BLU_PX 0x0000FF
#define  RED_PX 0xFF0000
#define  GRN_PX 0x00FF00
#define  SCALE 1

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

typedef struct s_vector
{
	double x;
	double y;
	double z;
	double nx;
	double ny;
	double nz;
	double magnitude;
	// double norm_vector;
	//t_color *color;
} t_vector;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_env {
	t_vector gravity;
	t_vector wind;
} t_env;

typedef struct s_proj{
	t_vector position;
	t_vector velocity;
} t_proj;


// typedef struct camera
// {
// 	t_vector pos;
// 	t_vector dir;
// 	t_vector up;
// 	t_vector right;
// } t_camera;

// typedef struct ray
// {
// 	t_vector origin;
// 	t_vector direction;
// } t_ray;

// typedef struct light
// {
// 	t_vector pos;
// 	t_vector color;
// } t_light;
// typedef struct ambient
// {
// 	float ratio;
// 	t_vector color;
// } t_ambient;

typedef struct data
{
	void *mlx_ptr;
	void *win_ptr;
	t_vector *vector;
	t_proj proj;
	t_env env;
} t_data;

int	handle_no_event(void *data);
int	handle_keypress(int keysym, t_data *data);
int	handle_keyrelease(int keysym, void *data);

double ft_sqr(double x);

// Vector functions
double vect_length(double x, double y, double z);
t_vector vect_addition(t_vector a, t_vector b);
t_vector vect_multiplication(t_vector a, double b);
t_vector normalize_vect(t_vector vector);
//double dot_product(t_vector a, t_vector b);
double cross_product_to_array(t_vector a, t_vector b);

t_proj tick(t_env *env, t_proj *proj);

// Color functions
int rgb_to_int(t_color color);
int	add_color(t_color *color1, t_color *color2);
int	substract_color(t_color *color1, t_color *color2);
int	multiply_color_by_scalar(t_color *color1, int scalar);
int	hadamard_product(t_color *color1, t_color *color2);