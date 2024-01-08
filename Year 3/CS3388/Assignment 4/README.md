
# CS3388 Assignment 4
Goal of this assignment is to get comfortable with triangular meshes and working with the camera in world space.

This program can:
- Manipulate the view amtrix so the camera appears to move around in world space
- Read triangle mesh data from the file
- Render textured triangle meshes using VBOs and VAOs

The program loads triangle mesh data and textures from files (inside of LinksHouse, within the same directory), renders them, and allows the user to explore that rendered world by moving the camera around via arrow keys.




## Usage/Examples
- Make sure you have all correct .ply files and .bmp files in a folder in the same directory named "LinksHouse"
Compile using
```
g++ Source.cpp -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW -lGLU -lstdc++fs      
```


## Screenshots

![App Screenshot](https://i.imgur.com/V538qha.png)
![App Screenshot](https://i.imgur.com/EzRNfHm.png)

