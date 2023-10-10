# Lab 5 - Introduction to OpenGL
## Overview
## Setup
### GLFW
- https://www.glfw.org/download.html
- 64-bit Windows binaries
- Decompress
- Navigate to C:\Users\Public
- Create folder named 'OpenGL' & create subfolder named 'GLFW'
- Enter downloaded GLFW folder & move files from 'include' to new 'GLFW' folder
- In downloaded GLFW folder, move 'lib-vc2022' to new 'OpenGL' folder & rename to 'lib'
- Open Visual Studio
- Create Empty C++ Project
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
## Initialisation
### GLFW
**CPP**
```c++
//GLAD
#include <glad/glad.h>

//GLFW
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}
```

### Window
**CPP**
```c++
GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5", NULL, NULL);

if (window == NULL)
{
    cout << "GLFW Window did not instantiate\n";
    glfwTerminate();
    return -1;
}

glfwMakeContextCurrent(window);

return 0;
```

### GLAD
**CPP**
```c++
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
	cout << "GLAD did not initialise\n";
	return -1;
}
```

### Viewport
#### Size
**CPP**
```c++
glViewport(0, 0, 1280, 720);
```

#### Resizing
**Header**
```c++
#pragma once

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
```

**CPP**
```c++
//STD
#include <iostream>

//GLAD
#include <glad/glad.h>

#include "main.h"

using namespace std;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5", NULL, NULL);

	if (window == NULL)
	{
		cout << "GLFW Window did not instantiate\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "GLAD did not initialise\n";
		return -1;
	}

	glViewport(0, 0, 1280, 720);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
```

### Render Loop
**CPP**
```c++
while (glfwWindowShouldClose(window) == false)
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

glfwTerminate();
```

### Input
**Header**
```c++
void processInput(GLFWwindow* window);
```

**CPP main()**
```c++
while (glfwWindowShouldClose(window) == false)
{
    //Input
	processInput(window);

    //Refreshing
	glfwSwapBuffers(window);
	glfwPollEvents();
}
```

**CPP processInput()**
```c++
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
```

### Rendering
**CPP**
```c++
while (glfwWindowShouldClose(window) == false)
{
	//Input
	processInput(window);

	//Rendering
	glClearColor(0.25f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Refreshing
	glfwSwapBuffers(window);
	glfwPollEvents();
}
```

## Drawing
### CPU Instantiation
**CPP Render**

Below ```glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);``` vv
```c++
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};
```
Above ```while (glfwWindowShouldClose(window) == false)``` ^^

### Vertex Buffer Objects
```c++
unsigned int vertexBufferObject;
glGenBuffers(1, &vertexBufferObject);
glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```