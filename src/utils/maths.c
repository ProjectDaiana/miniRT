# include "minirt.h"

double ft_sqr (double x)
{
	return (x * x);
}

double vect_lenght(double x, double y, double z)
{
	return sqrt(ft_sqr(x) + ft_sqr(y) + ft_sqr(z));
}

double dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector vect_addition(t_vector a, t_vector b)
{
	t_vector result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector vect_multiplication(t_vector a, double b)
{
	t_vector result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

double vect_length(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}

// double cross_product(t_vector a, t_vector b)
// {
// 	t_vector result;

// 	result.x = a.y * b.z - a.z * b.y;
// 	result.y = a.z * b.x - a.x * b.z;
// 	result.z = a.x * b.y - a.y * b.x;
// 	return (result);
// }

double cross_product_to_array(t_vector a, t_vector b)
{
	double result[3];
	result[0] = a.y * b.z - a.z * b.y;
	result[1] = a.z * b.x - a.x * b.z;
	result[2] = a.x * b.y - a.y * b.x;
	printf("Cross Product: %f, %f, %f\n", result[0], result[1], result[2]);
	return (*result);
}

t_proj tick(t_env *env, t_proj *proj)
{
	t_proj new_proj;

	new_proj.position = vect_addition(proj->position, proj->velocity);
	new_proj.velocity = vect_addition(proj->velocity, vect_addition(env->gravity, env->wind));
	printf(BLU"Projectile Position: (%f, %f, %f)\n" RESET, new_proj.position.x, new_proj.position.y, new_proj.position.z);
	printf(YEL"Projectile Velocity: (%f, %f, %f)\n" RESET, new_proj.velocity.x, new_proj.velocity.y, new_proj.velocity.z);
	return new_proj;
}