<div align="center">

MiniRT

A Hardware-Accelerated Raytracing Engine in C

<p align="center">
<em>A physically-based rendering engine built from scratch. It simulates light physics, geometric intersections, and shadows using vector mathematics.</em>
</p>

</div>

📖 About The Project

MiniRT is a minimalist Raytracer written in C. Unlike rasterization engines (like standard video games), MiniRT renders scenes by simulating light rays—tracing their path from a virtual camera, calculating intersections with 3D objects, and determining pixel color based on surface normals, light sources, and shadows.

This project was built with a focus on memory safety (using a custom Garbage Collector) and clean architecture.

✨ Core Features

Primitives: Renders Spheres, Planes, and Cylinders.

Lighting: Implements diffuse lighting and hard shadows.

Camera System: Fully movable camera with orientation vectors.

Scene Parsing: Custom .rt file parser with strict validation.

Memory Management: Custom GC implementation to prevent leaks (gc_malloc, gc_free_all).

Event Handling: Smooth keyboard interactions via hooks.

🛠️ Getting Started

Prerequisites

The project uses MLX42, which requires GLFW and CMake.

macOS (Homebrew):

brew install glfw cmake


Linux (Debian/Ubuntu):

sudo apt-get update
sudo apt-get install build-essential libglfw3-dev libglfw3 cmake xorg-dev


Installation

Clone the repository:

git clone [https://github.com/Neko-Bytes/minirt.git](https://github.com/Neko-Bytes/minirt.git)
cd minirt


Build the project:
This uses a standard Makefile that handles the MLX42 build automatically.

make


🎮 Usage

Run the executable with a scene file (.rt) as an argument:

./miniRT scenes/example.rt


⌨️ Controls

The engine features a real-time event loop for camera manipulation:

Key Action

Input

Move Forward

↑ (Arrow Up)

Move Backward

↓ (Arrow Down)

Strafe Left

← (Arrow Left)

Strafe Right

→ (Arrow Right)

Rotate Camera (Yaw)

A / D

Exit Program

ESC

📝 Scene Description Format (.rt)

The scene is defined in a simple configuration file.

1. Ambience (A)

Controls the background light of the scene.

A   0.2   255,255,255
#   Ratio  Color(R,G,B)


2. Camera (C)

Defines the viewpoint.

C   0,0,0    0,0,1      70
#   Pos(xyz) Orient(xyz) FOV


3. Light (L)

A point light source.

L   -10,10,20   0.6    255,255,255
#   Pos(xyz)    Bright Color


4. Objects (sp, pl, cy)

Sphere: sp  0,0,20  10  255,0,0 (Pos, Diameter, Color)

Plane: pl  0,0,0   0,1,0  0,0,255 (Pos, Normal, Color)

Cylinder: cy  50,0,20  0,1,0  14.2  21.4  10,0,255 (Pos, Axis, Diameter, Height, Color)

🧠 Technical Implementation

The Ray Casting Algorithm

For every pixel on the screen:

Ray Generation: A vector is calculated from the camera's origin through the specific pixel on the view plane.

Intersection Test: The ray is tested against every object in the scene using geometric formulas (e.g., Quadratic formula for spheres/cylinders).

Closest Hit: We find the intersection point closest to the camera (smallest valid $t$).

Lighting Calculation: We calculate the angle between the light source and the surface normal (Dot Product) to determine brightness.

Shadow Ray: A secondary ray is cast from the hit point to the light. If it hits another object, the point is in shadow.

Mathematical Toolkit

The engine relies heavily on linear algebra, implemented in src/math/:

Vector Operations: Dot product, Cross product, Normalization.

Matrix Transformations: Used for camera orientation and projection.

<div align="center">

View User Profile

</div>
