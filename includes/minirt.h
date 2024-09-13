# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/libft/libft.h"

# define W_HEIGHT 800
# define W_WIDTH 800
# define MLX_ERROR 1
# define MAX_SPHERES 10
# define BLU_PX 0x0000FF
# define RED_PX 0xFF0000
# define GRN_PX 0x00FF00
# define SCALE 100
# define M_PI 3.14159265358979323846
# define SQRT2_DIV2 (sqrt(2) / 2)

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
	// double nx;
	// double ny;
	// double nz;
	// double magnitude;
	// // double norm_vector;
	//t_color *color;
} t_vector;

typedef struct tuple
{
	double x;
	double y;
	double z;
	double w; // 1 for point, 0 for vector
} t_tuple;


typedef struct s_matrix
{
	double	**m;
	int size;
} t_matrix;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct
{
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	t_color		color;
}				t_material;

typedef struct
{
	t_vector	position;
	double		intensity;
	t_color		color;
}				t_light;

typedef struct
{
	t_vector	center;
	double		radius;
	t_material	material;
}				t_sphere;

typedef struct
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct
{
	int			hit;
	double		t;
	t_vector	point;
	t_vector	normal;
	t_material	material;
}				t_hit;

typedef struct s_camera
{
	t_vector	position;
	t_vector	rotation;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct
{
	t_sphere	sphere;
	t_camera	camera;
	t_light		light;
	t_color		ambient_color;
	double		ambient_intensity;
	void		*mlx;
	void		*win;
	// void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_img		img;
	// t_sphere	*spheres;
	int			sphere_count;
	int			max_spheres;
	t_sphere	spheres[MAX_SPHERES];
}				t_scene;

typedef struct data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	scene;

	t_vector *vector;
	t_tuple *tuple;
//	t_proj proj;
//	t_env env;
} t_data;

// Render
int		render_img(t_data *data);
int		render_frame(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// Event functions
int	handle_no_event(void *data);
int	handle_keypress(int keysym, t_data *data);
int	handle_keyrelease(int keysym, void *data);

//Parsing functions
int	parse_rt_file(char *filename, t_scene *scene);


// Vector functions
t_vector	vect_addition(t_vector a, t_vector b);
t_vector	vect_subtraction(t_vector a, t_vector b);
t_vector	vect_multiplication(t_vector a, double b);
t_vector	normalize_vect(t_vector vector);
double		vect_length(double x, double y, double z);
double		dot_product(t_vector a, t_vector b);
double		cross_product_to_array(t_vector a, t_vector b);

// Color & Lighting functions
t_color		create_color(int r, int g, int b);
t_color		calculate_lighting(t_hit hit, t_scene *scene, t_ray ray);
t_color		add_color(t_color color1, t_color color2);
t_color		substract_color(t_color color1, t_color color2);
t_color		multiply_color_by_scalar(t_color *color1, int scalar);
t_color		color_multiply(t_color a, t_color b);
//int	add_color(t_color *color1, t_color *color2);
//int	substract_color(t_color *color1, t_color *color2);
//int	multiply_color_by_scalar(t_color *color1, int scalar);
int			rgb_to_int(t_color color);
int			hadamard_product(t_color *color1, t_color *color2);

// Matrix functions
//t_matrix	create_matrix(double m[4][4]);
//t_matrix	create_matrix_3(double m[3][3]);
t_matrix	create_matrix(int size);
t_matrix	matrix_multiply(t_matrix a, t_matrix b);
t_matrix	transpose_matrix(t_matrix *identity_matrix);
t_matrix	find_submatrix(t_matrix *matrix, int row, int col, int mtrx_size);
t_matrix	inverse_matrix(t_matrix *matrix);
t_tuple		multiply_matrix_by_tuple(t_matrix *matrix, t_tuple *tuple);
void		assign_matrix(t_matrix *matrix, double m[4][4]);
//void		assign_matrix_3(t_matrix *matrix, double m[3][3]);
//double		calculate_determinant(double m[2][2]);
//double		calculate_determinant_m2(double **m, int size);
double		calculate_determinant(t_matrix *matrix, int size);
double		calculate_minor(t_matrix *matrix, int row, int col, int mtrx_size);
double		calculate_cofactor(t_matrix *matrix, int row, int col, int mtrx_size);
int			is_invertible(double det);
int			compare_matrix(t_matrix a, t_matrix b);


// Operations functions
t_matrix	translation(double x, double y, double z);
t_matrix	scaling(double x, double y, double z);
t_matrix	rotation_x(double rad);
t_matrix	rotation_y(double rad);
t_matrix	rotation_z(double rad);
t_matrix	skewing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);


// Ray functions
//t_ray	create_ray(double x, double y, t_camera *camera);
t_ray	create_ray(double x, double y);
t_hit	intersect_sphere(t_ray ray, t_sphere sphere);
t_color	trace_ray(t_ray ray, t_scene *scene);
t_hit	intersect_sphere(t_ray ray, t_sphere sphere);

//Scene functions
void	init_scene(t_scene *scene);
t_hit	intersect_scene(t_ray ray, t_scene *scene);

// Utility functions
double		double_to_degrees(double radians);
void		print_matrix(t_matrix matrix, char *str, int size);

// Error functions
void print_error(char *msg);

//Free functions
void	free_split(char **split);
void	free_matrix(t_matrix *matrix);



/// TEST FUNCTIONS, DELETE LATER
int check_rotation_results(t_tuple result_half, t_tuple result_full);
void draw_clock(t_data *data);
