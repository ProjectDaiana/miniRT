# miniRT: A Simple Raytracer in C with MiniLibX
Welcome to miniRT, a basic raytracing engine built from scratch using the MiniLibX graphical library. This project brings together essential concepts of computer graphics, particularly raytracing, to create realistic images of 3D scenes.

## Input Reference

#### Ambient lighting
- A
- ambient lighting ratio in range [0.0,1.0]: 0.2
- r, g, b

#### Camera
- C
- x, y, z,
- 3d normalized orientation vector. In range [-1,1] for each x,y,z,
- FOV  Horizontal field of view in degrees in range [0,180]: 70

#### Light
- L
- x, y, z,
- light_brightnes_ratio,
- r, g, b

#### Sphere
- sp	x, y, z,
- diameter,
- r, g, b

## Subject
[Subject](https://cdn.intra.42.fr/pdf/pdf/137465/en.subject.pdf)

## To Do
- [ ] Read file
- [ ] Check if file is valid
- [ ] Parse file
- [x] Create window
- [x] Handle keypress ESC
- [ ] Handle X button
- [ ] Create image
- [ ] Put pixel on screen

- [x] transform(r,m)
- [x] position(t_tuple *origin, t_tuple *direction, double t);
- [x] Changed t_vector to t_tuple;

## Features
- **Geometric Objects.** Supports rendering of basic geometric shapes including planes, spheres, and cylinders. These objects can be resized, translated, and rotated (except for spheres and lights, which cannot be rotated).
- **Lighting System.** Implements ambient and diffuse lighting, ensuring objects are illuminated realistically. The system also handles spot brightness and hard shadows, with no object ever being completely in the dark.
**Scene Description.** Scenes are defined in a flexible .rt file format. Each element, such as objects, lights, and cameras, can be described in any order, with parameters separated by spaces or line breaks.
- **Interactive Window Management.** The program displays the rendered image in a window that supports interactive features. Users can switch between windows, minimize the application, and close the window with ESC or the red close button, all while maintaining fluid performance.
- **Transformations.** Objects, lights, and cameras can undergo translation and rotation transformations, with specific properties like the diameter of a sphere or the width and height of a cylinder being adjustable.
- **Accurate Intersection Handling.** The program correctly manages all possible intersections and the insides of objects, ensuring accurate rendering of complex scenes.
- **MiniLibX Integration.** Utilizes the MiniLibX library for graphical output, adhering to the requirements for fluid window management and image handling.


## Resources
- [minilibx](https://aurelienbrabant.fr/blog?q=minilibx)
- [Basic Raytracing, Gabriel Gambetta](https://www.gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html)
- [Ray Tracer Youtube](https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv&index=1)
- [Ray Tracing in one Weekend](https://raytracing.github.io/)
- [The Ray Tracer Challenge](http://raytracerchallenge.com/)

## Maths 

#### Vector adition
	V + W =⟨Vx​ + Wx​, Vy​ + Wy​, Vz​ + Wz​⟩(for 3D vectors)

#### Vector substraction
	V - W = ⟨Vx​ - Wx​, Vy​ - Wy​, Vz​ - Wz​⟩(for 3D vectors)

#### Vector multiplication
	t * V = (t *Vx, t * Vy, t * Vz)

#### Component-Wise multiplication
	W * V = (Vx * Wx, Vy * Wy, Vz * Wz)

#### Scalar division
	vec.x *= 1 / t;
	vec.y *= 1 / t;
	vec.z *= 1 / t;

#### Unit vectors
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;

#### Vector Normalization
Convert any vector  with a nonzero magnitude into a unit vector.

    return tuple(v.x / magnitude(v),
                v.y / magnitude(v),
                v.z / magnitude(v),
                v.w / magnitude(v))

#### Dot/Scalar Product
If the two vectors are unit vectors, the dot product is actually the cosine of the angle between them. The smaller the dot product, the larger the angle between the vectors. Returns a scalar.

	V.W = Vx * Wx + Vy * Wy + Vz * Wz
	a.x * b.x + a.y * b.y + a.z * b.z

#### Cross Product
You get a new vector that is perpendicular to both of the original vectors. Returns a new vector.

    new.x = vec.y * vec2.z - vec.z * vec2.y;
    new.y = vec.z * vec2.x - vec.x * vec2.z;
    new.z = vec.x * vec2.y - vec.y * vec2.x;

#### Magnitude/Length of a vector (pythagoras)
	sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)
	ft_sqr(x) + ft_sqr(y) + ft_sqr(z);




