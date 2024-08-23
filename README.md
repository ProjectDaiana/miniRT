# miniRT: A Simple Raytracer in C with MiniLibX
Welcome to miniRT, a basic raytracing engine built from scratch using the MiniLibX graphical library. This project brings together essential concepts of computer graphics, particularly raytracing, to create realistic images of 3D scenes.


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
