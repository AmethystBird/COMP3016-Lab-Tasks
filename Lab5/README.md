# Lab 5 - Introduction to OpenGL
## Overview
OpenGL is a cross-platform application programming interface (API) specification. What this means is that OpenGL consists of a set of language & hardware independent functions that by itself is unable to interact with any system. For this reason, OpenGL serves as a standard that graphics drivers will then utilise & in some cases extend upon for additional functionality.

OpenGL is limited only to rendering, providing no features such as input, audio or even the ability to utilise a window to render to. For this reason, additional libraries will be needed in this lab. The installation process for them is detailed in the [Setup](#Setup) section.

A good resource for learning OpenGL is [LearnOpenGL](https://learnopengl.com/Introduction). The LearnOpenGL material will bare similarity to the material in these labs, however different libraries are used, so proceed with caution.

## Setup
### Prerequisites
Create an empty C++ Visual Studio project & create a new file named main.cpp in the `Source Files` filter.

It should not be necessary to install OpenGL, since it comes preinstalled on Windows, MacOS & Linux. However, if there are issues with OpenGL drivers, the [OpenGL Getting Started](https://www.khronos.org/opengl/wiki/Getting_Started) page will direct to the appropriate graphics driver sites.

Library & include files that will be downloaded in this lab will need to be placed in a new subfolder in the `C:\Users\Public` directory. Create a folder in this directory named `OpenGL` & inside this folder create two folders named `include` & `lib`.

### Linking
Your Visual Studio project's linker needs to know the locations of the library files that are going to be downloaded. The include files will be located at `C:\Users\Public\OpenGL\include` & the library files will be located at `C:\Users\Public\OpenGL\lib`. In order to link to these locations, go to your Visual Studio project, navigate to the `Solution Explorer`, right click the project file, select `Properties`, unfold `Configuration Properties` & select `VC++ Properties`. Add the include directory `C:\Users\Public\OpenGL\include` to the `Include Directories` section & add the library directory `C:\Users\Public\OpenGL\lib` to the `Library Directories` section respectively.

### GLFW
#### Overview
The GLFW library provides the ability to use OpenGL to render to windows, to receive input & also provides other useful events. In order to acquire GLFW, navigate to the [GLFW Download Page](https://www.glfw.org/download.html) & download the Windows pre-compiled 64-bit binaries.

#### Extraction
Open a file explorer & navigate to `C:\Users\Public\OpenGL` & open a second file explorer & navigate to the GLFW folder in the `Downloads` folder. In the GLFW folder, open the `include` subfolder & move the `GLFW` subfolder within that into the `include` folder in the `OpenGL` directory.

In the GLFW folder in the `Downloads` folder, many `lib-vc` folders exist. These library folders correspond to different versions of Visual C++. Open the `lib-vc2022` folder & move all the files into the `lib` folder in the `OpenGL` directory. In your main.cpp file, insert the ```#include <GLFW/glfw3.h>``` include. If Visual Studio fails to retrieve `glfw3.h`, then something has gone wrong in any of the aforementioned processes.

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

### OpenGL Extension Wrangler Library (GLEW)
#### Overview
GLEW is an extension loading library. It provides checks to determine what extensions are able to be supported on any particular targeted platform. To download it, go to the [GLEW Download Page](https://glew.sourceforge.net/) & select the GLEW Binaries for Windows 32-bit & 64-bit. After this, you will be redirected to another site where you will have to wait a few seconds for your download to start.

#### Extraction
Once you have downloaded GLEW, navigate to your `Downloads` folder. Open the `include` folder & move the `GL` folder into your `C:\Users\Public\OpenGL\include` directory. Additionally, in the GLEW folder, navigate to the `Release/x64` folder & move the files into the `C:\Users\Public\OpenGL\lib` directory. Then, in the GLEW folder, navigate to `bin/Release/x64` & move the `glew32.dll` file into your Visual Studio project's directory where your `main.cpp` file is located.

Lastly, in your Visual Studio Project's main.cpp file, add the ```#include <GL/glew.h>``` include. If Visual Studio fails to retrieve `glew.h`, then something has gone wrong in any of the aforementioned processes.

- Download from https://glew.sourceforge.net/
- Navigate to glew include folder & copy GL folder into `C:\Users\Public\OpenGL\include`
- Navigate to glew lib/Release/x64 folder & copy both `glew32.lib` & `glew32s.lib` to `C:\Users\Public\OpenGL\lib` alongside GLFW library files
- Navigate to glew bin/Release/x64 & copy glew32.dll into VS project directory; no need to 'add existing file' to project

### GLAD Alternative
#### Overview
In the [LearnOpenGL](https://learnopengl.com/Introduction) tutorial, the GLAD library is used as opposed to GLEW. If you are following the LearnOpenGL material, **you may wish to use GLAD, however I do not recommend this** either way, since this will require one to follow LearnOpenGL's error-prone system of implementing GLSL shaders into projects, which are needed at a basic level in this module & as the focus of the COMP3015 module. The `LoadShaders` header & cpp files in [Files](/Lab5/Files/) use GLEW & will allow for easier implementing of GLSL shaders. If you still wish to use GLAD, the process of retrieval is still available below.

#### Retrieval
GLAD can be downloaded from the [GLAD Loader-Generator Web Service](https://glad.dav1d.de/) in multiple different forms depending upon the individual's requirements. If one is to use GLAD for this lab, set the `Language` to `C++`, the `gl` to an OpenGL version of at least `Version 3.3` & lastly set the `Profile` to `Core`.

In the `Downloads` folder, open the `glad` folder & navigate to the `include` subfolder. Move both the internal `glad` & `KHR` folders to the `C:\Users\Public\OpenGL\include` folder. Then, in the `glad` folder's `lib` folder, move the `glad.c` file into your Visual Studio Project's project directory where your `main.cpp` file is located.

In your `main.cpp` file, add the ```//#include <glad/glad.h>``` include. If Visual Studio fails to retrieve `glad.h`, then something has gone wrong in any of the aforementioned processes.

### GLAD (Optional)
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

### GLEW
**CPP**
```c++
glewInit();
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

//framebuffer_size_callback() needs GLFW, so include moved here
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

	glewInit();

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

### CPU-GPU Conversion
#### Vertex Buffer Objects
**CPP**

Below ```float vertices[]``` vv
```c++
unsigned int vertexBufferObject;
glGenBuffers(1, &vertexBufferObject);
glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```
Above ```while (glfwWindowShouldClose(window) == false)``` ^^

#### Vertex Array Objects
**CPP Globals**
```c++
enum VAO_IDs {Triangles, Indices, Colours, Textures, NumVAOs = 2};
GLuint VAOs[NumVAOs];

enum Buffer_IDs { ArrayBuffer, NumBuffers = 4};
GLuint Buffers[NumBuffers];
```

**CPP main()**

Below ```float vertices[]``` vv
```c++
glGenVertexArrays(NumVAOs, VAOs);
glBindVertexArray(VAOs[0]);

glGenBuffers(NumBuffers, Buffers);

glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Unbinding
glBindVertexArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
```
Above ```while (glfwWindowShouldClose(window) == false)``` ^^

### GPU
#### Vertex Shader
**vertexShader.vert**
```GLSL
#version 460
layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
```

#### Fragment Shader
**fragmentShader.vert**
```GLSL
#version 460
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
```
#### Retrieval
**CPP Globals**
```c++
GLuint program;
```

//NOTE: Go back to check if LoadShaders is needed

**CPP main()**
Below ```glewInit();``` vv
```c++
ShaderInfo shaders[] =
{
	{ GL_VERTEX_SHADER, "shaders/vertexShader.vert" },
	{ GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag" },
	{ GL_NONE, NULL }
};

program = LoadShaders(shaders);
glUseProgram(program);
```
Above ```glViewport(0, 0, 1280, 720);``` ^^