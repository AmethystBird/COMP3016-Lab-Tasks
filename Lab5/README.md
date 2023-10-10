# Lab 5 - Introduction to OpenGL
## Overview
## Setup
### GLFW
#### Files
- https://www.glfw.org/download.html
- 64-bit Windows binaries
- Decompress
- Navigate to C:\Users\Public
- Create folder named 'OpenGL' & create subfolder named 'GLFW'
- Enter downloaded GLFW folder & move files from 'include' to new 'GLFW' folder
- In downloaded GLFW folder, move 'lib-vc2022' to new 'OpenGL' folder & rename to 'lib'
- Open Visual Studio
- Create Empty C++ Project
#### Linking
- In solution explorer, right click project & select properties at bottom
- Unfold Configuration Properties & select VC++ Properties
- Add include directory `C:\Users\Public\OpenGL\include`
- Add library directory `C:\Users\Public\OpenGL\lib`
- Unfold Linker, select Input & add both 'glfw3.lib' & 'opengl32.lib' to Additional Dependencies
- ```#include <GLFW/glfw3.h>``` in main.cpp
### GLAD
- https://glad.dav1d.de/
- Language C++, OpenGL Version 3.3>, Core, Generate a loader
- Download zip, go to glad/include & place 'glad' & 'KHR' folders in `C:\Users\Public\OpenGL\include`
- Go to glad/src & move or copy glad.c to VS project
- Add glad.c as existing file to source of VS project
- ```#include <glad/glad.h>``` above GLFW include in main.cpp

### GLM
- Go to https://github.com/g-truc/glm & download release .zip
- Navigate into glm & move the glm subfolder to `C:\Users\Public\OpenGL\include`