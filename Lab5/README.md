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