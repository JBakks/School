OpenGL Shapes with Marching Cubes

This is a project created by Josh Bakelaar that uses the OpenGL library to render various 3D shapes using the marching cubes algorithm.
Introduction

The marching cubes algorithm is a well-known algorithm used to create 3D models from volumetric data. It uses a series of cubes to generate a smooth surface that represents the shape of the original data. This project implements the marching cubes algorithm using OpenGL to create various 3D shapes.
Requirements

To run this project, you will need:

    OpenGL library (minimum version: OpenGL 3.3)
    CMake (minimum version: 3.12)

Installation

    Clone the repository to your local machine
    Navigate to the project directory
    Create a new directory called "build" and navigate into it
    Run the following command to generate the makefiles: cmake ..
    Run the following command to build the project: make
    Run the executable using ./opengl-shapes-marching-cubes

Usage

The program will open a window that displays a 3D shape generated using the marching cubes algorithm. You can use the following keyboard shortcuts to interact with the shape:

Credits

    OpenGL
    Marching Cubes Algorithm

License

This project is licensed under the MIT License - see the LICENSE file for details.