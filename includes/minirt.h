#include "../lib/libft/libft.h"
#include "../lib/minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define W_HEIGHT 800
#define W_WIDTH 800
#define MLX_ERROR 1
#define BLU_PX 0x0000FF
#define RED_PX 0xFF0000
#define GRN_PX 0x00FF00
#define SCALE 100
#define PI 3.14159265358979323846
#define SQRT2_DIV2 (sqrt(2) / 2)
#define MAX_SPHERES 10
#define EPSILON 0.00001
#define MAX_LIGHTS 10

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\033[0m"

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
	double		magnitude;

}				t_vector;

typedef struct tuple
{
	double		x;
	double		y;
	double		z;
	double w; // 1 for point, 0 for vector
}				t_tuple;

typedef struct s_matrix
{
	double		**m;
	int			size;
}				t_matrix;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct
{
	int			hit;
	double		t;
	t_vector	point;
	t_vector	normal;
}				t_hit;

typedef struct
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;

typedef struct
{
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	t_color		color;
}				t_material;


typedef struct s_canvas
{
	int			width;
	int			height;
	t_color		**pixels;
}				t_canvas;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct
{
	double		intensity;
	t_color		color;
	t_tuple		position;
}				t_light;

typedef struct s_camera
{
	double		fov;
	t_vector	origin;
	t_vector	lower_left_corner;
	t_vector	horizontal;
	t_vector	vertical;
	int			height;
	int			width;
	t_canvas	*canvas;
	double		pixel_size;
	double		half_width;
	double		half_height;
	t_matrix	transform;
	t_tuple		position;
	t_tuple		orientation;
	t_tuple		up;
	t_tuple		right;
}				t_camera;

typedef struct
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_sphere
{
	t_tuple		center;
	double		radius;
	t_material	material;
	t_color		color;
	t_matrix	transform;

}				t_sphere;

typedef struct s_plane
{
	t_tuple		point;
	t_tuple		normal;
	t_color		color;
	t_matrix	transform;
}				t_plane;

typedef struct s_cylinder
{
	double		diameter;
	double		height;
	double		max;
	double		min;
	t_tuple		center;
	t_tuple		axis;
	t_color		color;
	t_matrix	transform;
	t_material	material;

}				t_cylinder;

typedef struct
{
	double		ambient_intensity;
	t_color		ambient_color;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_light		*lights;
	int			light_count;
	t_sphere	*spheres;
	int			sphere_count;
	t_plane		*planes;
	int			plane_count;
	t_cylinder	*cylinders;
	int			cylinder_count;

}				t_scene;

typedef struct s_intersections
{
	int			count;
	double		t1;
	double		t2;
	double		*t;
	void		**object;
}				t_intersections;

typedef struct data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_vector	*vector;
	t_tuple		*tuple;
	t_img		img;
	t_scene		scene;

}				t_data;

typedef struct s_computations
{
	double		t;
	t_point		point;
	t_vector	over_point;
	t_vector	eyev;
	t_vector	normalv;
	t_vector	reflectv;
	double		n1;
	double		n2;
}				t_compu;

int				handle_no_event(void *data);
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, void *data);
int				close_window(t_data *data);

// Utility functions
double			ft_sqr(double x);
double			double_to_degrees(double radians);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				compare_tuple(t_tuple a, t_tuple b);


// Vector functions
double			vect_length(double x, double y, double z);
t_vector		vect_addition(t_vector a, t_vector b);
t_vector		vect_multiplication(t_vector a, double b);
t_tuple			normalize_vect(t_tuple v);

void			draw_clock(t_data *data);

// Color functions
int				rgb_to_int(t_color color);
int				add_color(t_color *color1, t_color *color2);
int				substract_color(t_color *color1, t_color *color2);
int				multiply_color_by_scalar(t_color *color1, int scalar);
int				hadamard_product(t_color *color1, t_color *color2);

t_color			create_color(double r, double g, double b);
t_color			color_add(t_color c1, t_color c2);
t_color			color_subtract(t_color c1, t_color c2);
t_color			color_multiply(t_color c, double scalar);
t_color			color_multiply_colors(t_color c1, t_color c2);

// Matrix functions
t_tuple			multiply_matrix_by_tuple(t_matrix matrix, t_tuple tuple);
t_matrix		create_matrix_3(double m[3][3]);
t_matrix		create_matrix(int size);
t_matrix		create_identity_matrix(void);
void			assign_matrix(t_matrix *matrix, double m[4][4]);
void			assign_matrix_3(t_matrix *matrix, double m[3][3]);

t_matrix		matrix_multiply(t_matrix a, t_matrix b);
t_matrix		transpose_matrix(t_matrix *identity_matrix);
t_matrix		find_submatrix(t_matrix *matrix, int row, int col,
					int mtrx_size);
double			calculate_determinant_m2(double **m, int size);
double			calculate_determinant(t_matrix *matrix, int size);
double			calculate_minor(t_matrix *matrix, int row, int col,
					int mtrx_size);
double			calculate_cofactor(t_matrix *matrix, int row, int col,
					int mtrx_size);
t_matrix		inverse_matrix(t_matrix *matrix);
int				is_invertible(double det);

int				compare_matrix(t_matrix a, t_matrix b);
void			print_matrix(t_matrix matrix, char *str, int size);

t_matrix		m_translation(double x, double y, double z);
t_matrix		scaling(double x, double y, double z);
t_matrix		rotation_x(double rad);
t_matrix		rotation_y(double rad);
t_matrix		rotation_z(double rad);
t_matrix		skewing(double x_y, double x_z, double y_x, double y_z,
					double z_x, double z_y);

// Error functions
void			print_error(char *msg);

/// TEST FUNCTIONS, DELETE LATER
int				check_rotation_results(t_tuple result_half,
					t_tuple result_full);
void test_truncated_cylinders();

t_tuple			point(double x, double y, double z, double w);
void			test_intersection(t_tuple origin, t_tuple direction);

t_ray			transform(t_ray *ray, t_matrix *matrix);

double			vect_lenght(double x, double y, double z);

double			dot_product(t_vector a, t_vector b);

double			cross_product_to_array(t_vector a, t_vector b);

// tuple functions
t_tuple			create_tuple(double x, double y, double z, double w);

t_tuple			create_point(double x, double y, double z);
t_tuple			create_vector(double x, double y, double z);

t_tuple			tuple_add(t_tuple a, t_tuple b);

t_tuple			tuple_subtract(t_tuple a, t_tuple b);
t_tuple			tuple_negate(t_tuple a);
t_tuple			tuple_multiply(t_tuple a, double scalar);
t_tuple			tuple_divide(t_tuple a, double scalar);
double			tuple_magnitude(t_tuple a);
t_tuple			tuple_normalize(t_tuple a);

double			tuple_dot(t_tuple a, t_tuple b);
t_tuple			tuple_cross(t_tuple a, t_tuple b);

// render function
int				render(t_data *data);


// canvas functions
t_canvas		create_canvas(int width, int height);
void			write_pixel(t_canvas *canvas, int x, int y, t_color color);
void			free_canvas(t_canvas *canvas);
t_color			pixel_at(t_canvas *canvas, int x, int y);
void			canvas_to_ppm(t_canvas *canvas, const char *filename);

// ray functions
t_ray			create_ray(t_tuple origin, t_tuple direction);
t_tuple			position(t_ray ray, double t);

// sphere functions
t_sphere		create_sphere(void);
t_intersections	intersect_sphere(t_sphere sphere, t_ray ray);
t_tuple			normal_at(t_sphere sphere, t_tuple world_point);
t_tuple			normal_at_sphere(t_sphere sphere, t_tuple world_point);


// cylinder functions
t_cylinder		create_cylinder(void);
t_tuple			normal_at_cylinder(t_cylinder cylinder, t_tuple world_point);
t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray);
void			intersect_caps(t_cylinder cylinder, t_ray ray, t_intersections *result);
void	truncate_cylinder(t_cylinder *cylinder, double t1, double t2);


// lighting functions
t_color			lighting(t_material material, t_light light, t_tuple point,
					t_tuple eye_v, t_tuple normal_v, int in_shadow);

// parser functions
void			parse_scene(const char *filename, t_scene *scene);

// object functions
void			add_light(t_scene *scene, t_light *light);
void			add_sphere(t_scene *scene, t_sphere *sphere);
void			add_plane(t_scene *scene, t_plane *plane);
void			add_cylinder(t_scene *scene, t_cylinder *cylinder);

// intersections
t_intersections	intersect_plane(t_plane plane, t_ray ray);
t_tuple			normal_at_plane(t_plane plane, t_tuple point);
t_intersections	intersect_cylinder(t_cylinder cylinder, t_ray ray);
t_tuple			normal_at_cylinder(t_cylinder cylinder, t_tuple point);
void			sort_intersections(t_intersections *xs);
t_intersections	intersect_world(t_scene *scene, t_ray ray);
int				is_shadowed(t_scene *scene, t_tuple point, t_light *light);

t_ray			transform_ray(t_ray ray, t_matrix transform);
void			set_transform(t_sphere *sphere, t_matrix transform);
t_tuple			matrix_multiply_tuple(t_matrix m, t_tuple t);
t_color			ray_color(t_scene *scene, t_ray ray);
t_ray			ray_for_pixel(t_camera *camera, int px,
					int py);
t_tuple tuple_reflect(t_tuple in, t_tuple normal);