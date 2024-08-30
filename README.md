# miniRT: A Simple Raytracer in C with MiniLibX
Welcome to miniRT, a basic raytracing engine built from scratch using the MiniLibX graphical library. This project brings together essential concepts of computer graphics, particularly raytracing, to create realistic images of 3D scenes.

## To Do
- [ ] Read file
- [ ] Check if file is valid
- [ ] Parse file
- [x] Create window
- [x] Handle keypress ESC
- [ ] Handle X button
- [ ] Create image
- [ ] Put pixel on screen

- [ ] Normalize vectors 🐱
- [ ] Calcualate color of pixel

## Subject
[Subject](https://cdn.intra.42.fr/pdf/pdf/137465/en.subject.pdf)

## Features
#### Geometric Objects
Supports rendering of basic geometric shapes including planes, spheres, and cylinders. These objects can be resized, translated, and rotated (except for spheres and lights, which cannot be rotated).
#### Lighting System
Implements ambient and diffuse lighting, ensuring objects are illuminated realistically. The system also handles spot brightness and hard shadows, with no object ever being completely in the dark.
#### Scene Description
Scenes are defined in a flexible .rt file format. Each element, such as objects, lights, and cameras, can be described in any order, with parameters separated by spaces or line breaks.
#### Interactive Window Management
The program displays the rendered image in a window that supports interactive features. Users can switch between windows, minimize the application, and close the window with ESC or the red close button, all while maintaining fluid performance.
#### Transformations
Objects, lights, and cameras can undergo translation and rotation transformations, with specific properties like the diameter of a sphere or the width and height of a cylinder being adjustable.
#### Accurate Intersection Handling
The program correctly manages all possible intersections and the insides of objects, ensuring accurate rendering of complex scenes.
#### MiniLibX Integration
Utilizes the MiniLibX library for graphical output, adhering to the requirements for fluid window management and image handling.


## Resources
- [minilibx](https://aurelienbrabant.fr/blog?q=minilibx)
- [Basic Raytracing, Gabriel Gambetta](https://www.gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html)
- [Ray Tracer Youtube](https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv&index=1)
- [Ray Tracing in one Weekend](https://raytracing.github.io/)
- [The Ray Tracer Challenge](http://raytracerchallenge.com/)

## Maths 
#### Calculate the length of a vector
sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)
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
#### Dot Product
V.W = Vx * Wx + Vy * Wy + Vz * Wz
vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z
#### Cross Product
    new.x = vec.y * vec2.z - vec.z * vec2.y;
    new.y = vec.z * vec2.x - vec.x * vec2.z;
    new.z = vec.x * vec2.y - vec.y * vec2.x;
