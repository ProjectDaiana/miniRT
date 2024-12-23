#include "minirt.h"
#include <stdio.h>

void test_plane_intersections(void)
{
    printf("\nTesting plane intersections...\n");
    t_plane plane = {0};
    t_ray ray;
    
    // Setup plane
    plane.point = create_point(0, 0, 0);
    plane.normal = create_vector(0, 1, 0);
    
    // Test case 1: Ray intersects plane
    ray.origin = create_point(0, 5, 0);
    ray.direction = create_vector(0, -1, 0);
    t_intersections xs = intersect_plane(&plane, ray);
    printf("Intersection count: %d\n", xs.count);
    free_intersections(&xs);

    // Test case 2: Ray parallel to plane
    ray.direction = create_vector(0, 0, 1);
    xs = intersect_plane(&plane, ray);
    printf("Parallel ray intersection count: %d\n", xs.count);
    free_intersections(&xs);
}

void test_sphere_intersections(void)
{
    printf("\nTesting sphere intersections...\n");
    t_sphere sphere = {0};
    t_ray ray;
    
    // Setup sphere
    sphere.center = create_point(0, 0, 0);
    sphere.radius = 1.0;
    
    // Test case 1: Ray hits sphere
    ray.origin = create_point(0, 0, -5);
    ray.direction = create_vector(0, 0, 1);
    t_intersections xs = intersect_sphere(sphere, ray);
    printf("Intersection count: %d\n", xs.count);
    free_intersections(&xs);

    // Test case 2: Ray misses sphere
    ray.origin = create_point(2, 2, -5);
    xs = intersect_sphere(sphere, ray);
    printf("Miss intersection count: %d\n", xs.count);
    free_intersections(&xs);
}

void test_cylinder_intersections(void)
{
    printf("\nTesting cylinder intersections...\n");
    t_cylinder cylinder = {0};
    t_ray ray;
    
    // Setup cylinder
    cylinder.center = create_point(0, 0, 0);
    cylinder.axis = create_vector(0, 1, 0);
    cylinder.diameter = 2.0;
    cylinder.height = 2.0;
    
    // Test case 1: Ray hits cylinder body
    ray.origin = create_point(3, 0, 0);
    ray.direction = create_vector(-1, 0, 0);
    t_intersections xs = intersect_cylinder(cylinder, ray);
    printf("Body intersection count: %d\n", xs.count);
    free_intersections(&xs);

    // Test case 2: Ray hits cylinder cap
    ray.origin = create_point(0, 2, 0);
    ray.direction = create_vector(0, -1, 0);
    xs = intersect_cylinder(cylinder, ray);
    printf("Cap intersection count: %d\n", xs.count);
    free_intersections(&xs);
}

void test_world_intersections(void)
{
    printf("\nTesting world intersections...\n");
    t_scene scene = {0};
    t_ray ray;
    
    // Setup simple scene
    scene.sphere_count = 1;
    scene.spheres = malloc(sizeof(t_sphere));
    scene.spheres[0].center = create_point(0, 0, 0);
    scene.spheres[0].radius = 1.0;
    
    // Test world intersection
    ray.origin = create_point(0, 0, -5);
    ray.direction = create_vector(0, 0, 1);
    t_intersections xs = intersect_world(&scene, ray);
    printf("World intersection count: %d\n", xs.count);
    free_intersections(&xs);
    
    free(scene.spheres);
}

int main(void)
{
    test_plane_intersections();
    test_sphere_intersections();
    test_cylinder_intersections();
    test_world_intersections();
    
    return 0;
}
 