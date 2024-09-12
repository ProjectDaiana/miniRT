#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define W_WIDTH 800
# define W_HEIGHT 800
# define MLX_ERROR 1
# define MAX_SPHERES 10

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
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct
{
	double		m[4][4];
}				t_matrix;

typedef struct
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_tuple;

typedef struct
{
	t_vector	position;
	t_vector	velocity;
}				t_proj;

typedef struct
{
	t_vector	gravity;
	t_vector	wind;
}				t_env;

typedef struct
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct
{
	t_vector	origin;
	t_vector	direction;
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

typedef struct
{
	t_vector	center;
	double		radius;
	t_material	material;
}				t_sphere;

typedef struct
{
	t_vector	position;
	double		intensity;
	t_color		color;
}				t_light;

typedef struct
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_camera
{
	t_vector	position;
	t_vector	rotation;
	t_vector	orientation;
	double		fov;
}				t_camera;

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
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_scene		scene;

}				t_data;

typedef struct
{
	int			hit;
	double		t;
	t_vector	point;
	t_vector	normal;
	t_material	material;
}				t_hit;

int				handle_no_event(void *data);
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, void *data);
int				rgb_to_int(t_color color);
t_color			add_color(t_color color1, t_color color2);

// int				add_color(t_color *color1, t_color *color2);
t_color			multiply_color_by_scalar(t_color color1, double scalar);

int				substract_color(t_color *color1, t_color *color2);
int				hadamard_product(t_color *color1, t_color *color2);
double			ft_sqr(double x);
double			vect_lenght(double x, double y, double z);
double			dot_product(t_vector a, t_vector b);
t_vector		vect_addition(t_vector a, t_vector b);
t_vector		vect_multiplication(t_vector a, double b);
// double			vect_length(double x, double y, double z);
double			cross_product_to_array(t_vector a, t_vector b);
t_proj			tick(t_env *env, t_proj *proj);
t_matrix		create_matrix(double m[4][4]);
void			print_matrix(t_matrix matrix);
int				compare_matrix(t_matrix a, t_matrix b);
t_matrix		matrix_multiply(t_matrix a, t_matrix b);
t_tuple			multiply_matrix_by_tuple(t_matrix *matrix, t_tuple *tuple);

// added for checks?
// t_ray			create_ray(double x, double y);
// int				trace_ray(Ray ray);
t_color			trace_ray(t_ray ray, t_scene *scene);
int				render_frame(t_data *data);
t_hit			intersect_sphere(t_ray ray, t_sphere sphere);
t_color			calculate_lighting(t_hit hit, t_scene *scene, t_ray ray);
void			init_scene(t_scene *scene);
void			render(t_scene *scene);
t_hit			intersect_scene(t_ray ray, t_scene *scene);

t_vector		vect_normalize(t_vector v);
t_vector		vect_reflect(t_vector v, t_vector n);
t_vector		vect_negate(t_vector v);
t_color			color_multiply(t_color a, t_color b);
t_vector		vect_subtraction(t_vector a, t_vector b);
double			vect_length(t_vector v);
void			put_pixel(t_data *data, int x, int y, int color);
t_color			create_color(int r, int g, int b);
t_ray			create_ray(double x, double y, t_camera *camera);

t_color			scale_color(t_color color, double factor);

t_tuple			create_point(double x, double y, double z);

t_tuple			create_vector(double x, double y, double z);

t_tuple			normalize_vector(t_tuple v);

t_vector		vector_from_tuple(t_tuple t);

int				parse_color(char *str, t_color *color);

int				parse_vector(char *str, t_vector *vector);

int				parse_ambient(char **split, t_scene *scene);

int				parse_camera(char **split, t_scene *scene);

int				parse_light(char **split, t_scene *scene);

int				parse_sphere(char **split, t_scene *scene);

int				parse_line(char *line, t_scene *scene);

int				parse_rt_file(char *filename, t_scene *scene);
int				get_next_line(int fd, char **line);
void			free_split(char **split);
t_matrix		create_identity_matrix(void);

t_matrix		create_translation_matrix(double x, double y, double z);
t_matrix		create_scaling_matrix(double x, double y, double z);

t_matrix		inverse_matrix(t_matrix m);

t_matrix		create_rotation_x_matrix(double angle);

t_matrix		create_rotation_y_matrix(double angle);
t_matrix		create_rotation_z_matrix(double angle);
t_vector		apply_matrix_to_vector(t_matrix m, t_vector v);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif