#include "../lib/libft/libft.h"
#include "../lib/minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define W_HEIGHT 800
#define W_WIDTH 800
#define MLX_ERROR 1
#define BLU_PX 0x0000FF
#define RED_PX 0xFF0000
#define GRN_PX 0x00FF00
#define SCALE 100
#define M_PI 3.14159265358979323846
#define SQRT2_DIV2 (sqrt(2) / 2)
#define MAX_SPHERES 10
#define EPSILON 0.00001
#define MAX_LIGHTS 10
#define MAX_REFLECTION_DEPTH 5
#define EPSILON 0.00001
#define THREADS 4

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
	double			x;
	double			y;
	double			z;
	double			magnitude;

}					t_vector;

typedef struct tuple
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_tuple;

typedef struct s_matrix
{
	double			**m;
	int				size;
}					t_matrix;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_hit
{
	int				hit;
	double			t;
	t_tuple			point;
	t_tuple			normal;
	t_tuple			eyev;
	t_tuple			normalv;
	t_tuple			over_point;
	int				inside;
}					t_hit;

typedef struct
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

typedef struct s_canvas
{
	int				width;
	int				height;
	t_color			**pixels;
}					t_canvas;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct
{
	double			intensity;
	t_color			color;
	t_tuple			position;
}					t_light;

typedef struct s_camera
{
	double			fov;
	t_vector		origin;
	t_vector		lower_left_corner;
	t_vector		horizontal;
	t_vector		vertical;
	int				height;
	int				width;
	t_canvas		*canvas;
	double			pixel_size;
	double			half_width;
	double			half_height;
	t_matrix		transform;
	t_tuple			position;
	t_tuple			orientation;
	t_tuple			up;
	t_tuple			right;
	int				hsize;
	int				vsize;
}					t_camera;

typedef struct
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef enum e_pattern_type
{
	SOLID,
	CHECKERS
}					t_pattern_type;

typedef struct s_pattern
{
	t_pattern_type	type;
	t_color			color1;
	t_color			color2;
	t_matrix		transform;
}					t_pattern;

typedef struct s_material
{
	t_color			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	double			reflective;
	t_pattern		pattern;
	int				has_pattern;
	double			transparency;

}					t_material;

typedef struct s_sphere
{
	t_tuple			center;
	double			radius;
	t_material		material;
	t_color			color;
	int				type;

}					t_sphere;

typedef struct s_plane
{
	t_tuple			point;
	t_tuple			normal;
	t_color			color;
	t_matrix		transform;
	t_material		material;
	int				type;

}					t_plane;

typedef struct s_cylinder
{
	t_tuple			center;
	t_tuple			axis;
	double			diameter;
	double			height;
	t_color			color;
	t_matrix		transform;
	double			max;
	double			min;
	t_material		material;
	int				type;
}					t_cylinder;

typedef struct s_ambient_light
{
	t_color			color;
	double			intensity;
}					t_ambient_light;

typedef struct
{
	double			ambient_intensity;
	t_color			ambient_color;
	t_camera		camera;
	t_light			light;
	t_sphere		sphere;
	t_light			*lights;
	int				light_count;
	t_sphere		*spheres;
	int				sphere_count;
	t_plane			*planes;
	int				plane_count;
	t_cylinder		*cylinders;
	int				cylinder_count;
	t_ambient_light	ambient_light;
	int				max_spheres;
}					t_scene;

typedef struct s_intersections
{
	int				count;
	double			t1;
	double			t2;
	double			*t;
	void			**object;
}					t_intersections;

typedef struct data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_vector		*vector;
	t_tuple			*tuple;
	t_img			img;
	t_light			light;
	t_scene			scene;

}					t_data;

typedef struct s_computations
{
	double			t;
	t_tuple			point;
	t_tuple			over_point;
	t_tuple			eyev;
	t_tuple			normalv;
	t_tuple			reflectv;
	double			n1;
	double			n2;
	void			*object;
	int				inside;
}					t_compu;

typedef struct s_world
{
	t_sphere		*spheres;
	int				sphere_count;
	t_light			*lights;
	int				light_count;
}					t_world;

typedef struct s_light_data
{
	t_material		material;
	t_light			light;
	t_tuple			point;
	t_tuple			eye_v;
	t_tuple			normal_v;
	int				in_shadow;
}					t_light_data;

typedef struct s_lighting_params
{
	t_material		material;
	t_light			light;
	t_tuple			point;
	t_tuple			eye_v;
	t_tuple			normal_v;
	int				in_shadow;
}					t_lighting_params;

typedef struct s_submatrix_data
{
	int				col;
	int				sub_i;
}					t_submatrix_data;

typedef struct s_skew_params
{
	double			x_y;
	double			x_z;
	double			y_x;
	double			y_z;
	double			z_x;
	double			z_y;
}					t_skew_params;

typedef struct {
    t_canvas		*canvas;
    t_scene			*scene;
    t_camera		*camera;
    int				start_y;
    int				end_y;
} 					t_thread_data;

int					handle_no_event(void *data);
int					handle_keypress(int keysym, t_data *data);
int					handle_keyrelease(int keysym, void *data);

double				ft_sqr(double x);
double				double_to_degrees(double radians);

double				vect_length(double x, double y, double z);
t_vector			vect_addition(t_vector a, t_vector b);
t_vector			vect_multiplication(t_vector a, double b);
t_tuple				normalize_vect(t_tuple v);

void				draw_clock(t_data *data);

int					rgb_to_int(t_color color);
int					add_color(t_color *color1, t_color *color2);
int					substract_color(t_color *color1, t_color *color2);
int					multiply_color_by_scalar(t_color *color1, int scalar);
int					hadamard_product(t_color *color1, t_color *color2);

t_color				create_color(double r, double g, double b);
t_color				color_add(t_color c1, t_color c2);
t_color				color_subtract(t_color c1, t_color c2);
t_color				color_multiply(t_color c, double scalar);
t_color				color_multiply_colors(t_color c1, t_color c2);

t_tuple				multiply_matrix_by_tuple(t_matrix *matrix, t_tuple *tuple);
t_matrix			create_matrix_3(double m[3][3]);
t_matrix			create_matrix(int size);
void				assign_matrix(t_matrix *matrix, double m[4][4]);
void				assign_matrix_3(t_matrix *matrix, double m[3][3]);

t_matrix			matrix_multiply(t_matrix a, t_matrix b);
t_matrix			transpose_matrix(t_matrix *identity_matrix);
t_matrix			find_submatrix(t_matrix *matrix, int row, int col,
						int mtrx_size);
double				calculate_determinant_m2(double **m, int size);
double				calculate_determinant(t_matrix *matrix, int size);
double				calculate_minor(t_matrix *matrix, int row, int col,
						int mtrx_size);
double				calculate_cofactor(t_matrix *matrix, int row, int col,
						int mtrx_size);
t_matrix			inverse_matrix(t_matrix *matrix);
int					is_invertible(double det);

int					compare_matrix(t_matrix a, t_matrix b);
void				print_matrix(t_matrix matrix, char *str, int size);

t_matrix			translation(double x, double y, double z);
t_matrix			scaling(double x, double y, double z);
t_matrix			rotation_x(double rad);
t_matrix			rotation_y(double rad);
t_matrix			rotation_z(double rad);
t_matrix			skewing(t_skew_params params);

void				print_error(char *msg);

/// TEST FUNCTIONS, DELETE LATER
int					check_rotation_results(t_tuple result_half,
						t_tuple result_full);

t_tuple				point(double x, double y, double z, double w);
void				test_intersection(t_tuple origin, t_tuple direction);

t_ray				transform(t_ray *ray, t_matrix *matrix);

double				vect_lenght(double x, double y, double z);

double				dot_product(t_vector a, t_vector b);

double				cross_product_to_array(t_vector a, t_vector b);

t_tuple				create_tuple(double x, double y, double z, double w);

t_tuple				create_point(double x, double y, double z);
t_tuple				create_vector(double x, double y, double z);

t_tuple				tuple_add(t_tuple a, t_tuple b);

t_tuple				tuple_subtract(t_tuple a, t_tuple b);
t_tuple				tuple_negate(t_tuple a);
t_tuple				tuple_multiply(t_tuple a, double scalar);
t_tuple				tuple_divide(t_tuple a, double scalar);
double				tuple_magnitude(t_tuple a);
t_tuple				tuple_normalize(t_tuple a);

double				tuple_dot(t_tuple a, t_tuple b);
t_tuple				tuple_cross(t_tuple a, t_tuple b);

int					render(t_data *data);

t_canvas			create_canvas(int width, int height);
void				write_pixel(t_canvas *canvas, int x, int y, t_color color);
void				free_canvas(t_canvas *canvas);
t_color				pixel_at(t_canvas *canvas, int x, int y);
void				canvas_to_ppm(t_canvas *canvas, const char *filename);

t_ray				create_ray(t_tuple origin, t_tuple direction);
t_tuple				position(t_ray ray, double t);

t_sphere			create_sphere(void);
t_intersections		intersect_sphere(t_sphere sphere, t_ray ray);

void				parse_scene(const char *filename, t_scene *scene);

void				my_mlx_pixel_put(t_img *img, int x, int y, int color);

void				add_light(t_scene *scene, t_light *light);
void				add_sphere(t_scene *scene, t_sphere *sphere);
void				add_plane(t_scene *scene, t_plane *plane);
void				add_cylinder(t_scene *scene, t_cylinder *cylinder);

t_intersections		intersect_plane(t_plane *plane, t_ray ray);
t_intersections		intersect_cylinder(t_cylinder cylinder, t_ray ray);
t_tuple				normal_at_cylinder(t_cylinder *cylinder,
						t_tuple world_point);
void				sort_intersections(t_intersections *xs);
t_intersections		intersect_world(t_scene *scene, t_ray ray);
int					is_shadowed(t_scene *scene, t_tuple point, t_light *light);

t_ray				transform_ray(t_ray ray, t_matrix transform);
t_tuple				matrix_multiply_tuple(t_matrix m, t_tuple t);
t_color				ray_color(t_scene *scene, t_ray ray);
t_ray				ray_for_pixel(t_camera *camera, int px, int py);

t_tuple				tuple_reflect(t_tuple in, t_tuple normal);
void				intersect_body(double a, double b, double c,
						t_intersections *result, t_cylinder cylinder,
						t_ray ray);
void				ft_free_split(char **split);
double				ft_atof(const char *str);
t_plane				create_plane(t_tuple point, t_tuple normal, t_color color);
t_compu				prepare_computations(double t, t_ray ray,
						t_intersections *xs);
t_matrix			create_identity_matrix(void);

t_camera			create_camera(int hsize, int vsize, double field_of_view);
t_matrix			look_at(t_tuple from, t_tuple to, t_tuple up);
t_tuple				normal_at(void *object, t_tuple world_point);

t_tuple				normal_at_sphere(t_sphere *sphere, t_tuple world_point);
t_tuple				normal_at_plane(t_plane *plane, t_tuple world_point);

t_pattern			create_checkers_pattern(t_color c1, t_color c2);
t_color				pattern_at_checkers(t_pattern pattern, t_tuple point);
t_color				pattern_at(t_pattern pattern, t_tuple point);
t_color				pattern_at_shape(t_pattern pattern, void *shape,
						t_tuple world_point);
t_color				reflected_color(t_scene *scene, t_compu comps,
						int remaining);
t_color				shade_hit(t_scene *scene, t_compu comps, int remaining);
t_color				color_at(t_scene *scene, t_ray ray, int remaining);

int					validate_params(char **split, int count, char *element);

int					validate_coordinates(char **coords, char *element,
						char **to_free);

void				free_splits(char **split1, char **split2, char **split3);
int					is_valid_line(char *line);

t_color				create_material_color(char **color_values);

void				init_sphere_material(t_sphere *sphere);

double				schlick(t_compu comps);
void				set_color_components(t_color *dest, char **color_values);

void				set_camera_orientation(t_scene *scene, char **orient);
void				set_camera_position(t_scene *scene, char **pos);
void				set_sphere_center(t_sphere *sphere, char **pos);
int					init_plane_splits(char *line, char ***split, char ***pos,
						char ***normal);

int					init_plane_color(char **split, char ***color);
void				init_scene_file(const char *filename, FILE **file,
						t_scene *scene);
void				parse_line_by_type(char *line, t_scene *scene);
void				parse_scene(const char *filename, t_scene *scene);
void				parse_ambient(char *line, t_scene *scene);
void				parse_camera(char *line, t_scene *scene);
void				parse_light(char *line, t_scene *scene);
void				parse_sphere(char *line, t_scene *scene);
void				parse_plane(char *line, t_scene *scene);
void				init_scene_file(const char *filename, FILE **file,
						t_scene *scene);
t_plane				create_plane_from_params(char **pos, char **normal,
						char **color);

t_material			get_object_material(void *object);
t_tuple				get_object_normal(void *object, t_tuple point);

t_color				get_reflection_color(t_scene *scene, t_ray reflect_ray,
						void *reflect_object, t_tuple reflect_point);

t_color				calculate_reflection_color(t_scene *scene,
						t_intersections reflect_xs, t_ray reflect_ray);

t_color				calculate_reflection(t_scene *scene, t_ray ray,
						t_tuple point, t_tuple normal);

t_color				get_surface_color(t_scene *scene, t_material material,
						t_compu comps);
t_color				get_base_color(t_material material, t_tuple point);

t_color				get_ambient_component(t_color base_color,
						t_light_data *light_data);

t_color				get_diffuse_component(t_color base_color,
						t_light_data *light_data, double dot);
t_color				get_specular_component(t_light_data *light_data,
						double reflect_dot);
t_color				lighting(t_lighting_params params);

void				init_cylinder_intersection(t_intersections *result);
void				calculate_cylinder_params(t_cylinder cylinder, t_ray ray,
						double *params);
void				add_valid_intersection(t_intersections *result, double t,
						t_cylinder *cylinder, int *index);

void				calculate_cylinder_intersections(t_cylinder cylinder,
						t_ray ray, double *t, double *y);

void				check_cylinder_bounds(t_cylinder cylinder, double *t,
						double *y);
void				allocate_intersections(t_intersections *result, double *t,
						t_cylinder *cylinder);

void				calculate_sphere_params(t_ray ray, t_sphere sphere,
						double *params);
void				init_intersection_result(t_intersections *result,
						double discriminant);
void				set_intersection_values(t_intersections *result,
						t_sphere *sphere, double *params);
int					init_mlx(t_data *data);
void				setup_hooks(t_data *data);
void				free_scene(t_scene *scene);
void				free_intersections(t_intersections *xs);
void				parse_cylinder(char *line, t_scene *scene);
void				calculate_t(double *t1, double *t2, double discriminant,
						double a, double b);

void				intersect_caps(t_cylinder cylinder, t_ray ray,
						t_intersections *result);
void				add_intersection(t_intersections *result, double t);
int					check_cap(t_ray ray, double t, t_cylinder cylinder);

void				init_cylinder_material(t_cylinder *cylinder);

t_tuple				transform_point(t_matrix transform, t_tuple point);
void				init_plane_material(t_plane *plane, t_color color);
void				set_orientation_matrix(t_matrix *matrix, t_tuple left,
						t_tuple true_up, t_tuple forward);
void				add_sphere_intersections(t_scene *scene, t_ray ray,
						t_intersections *result);
void				add_plane_intersections(t_scene *scene, t_ray ray,
						t_intersections *result);
void				add_cylinder_intersections(t_scene *scene, t_ray ray,
						t_intersections *result);