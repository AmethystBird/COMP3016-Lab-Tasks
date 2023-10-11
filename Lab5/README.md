# Lab 5 - Introduction to OpenGL
## Overview
OpenGL is a cross-platform application programming interface (API) specification. What this means is that OpenGL consists of a set of language & hardware independent functions that by itself is unable to interact with any system. For this reason, OpenGL serves as a standard that graphics drivers will then utilise & in some cases extend upon for additional functionality.

OpenGL is limited only to rendering, providing no features such as input, audio or even the ability to utilise a window to render to. For this reason, additional libraries will be needed in this lab. The download process for them is detailed in the [Setup](#Setup) section.

A good resource for learning OpenGL is [LearnOpenGL](https://learnopengl.com/Introduction). The LearnOpenGL material will bare similarity to the material in these labs, however different libraries are used, so proceed with caution.

## Setup
### Project
#### Prerequisites
In Visual Studio, create an `Empty Project` that uses C++. Next, create a new file named main.cpp in the `Source Files` filter. For GLSL shader functionality, you will also need to acquire the `LoadShaders` header & cpp files from [Files](/Lab5/Files/). Once they have been downloaded, right click your project file in the `Solution Explorer` & select `Open folder in File Explorer`. Create a new folder named 'shaders' & place the `LoadShaders` header & cpp files inside it. Next, go back to Visual Studio, right click the project file, select `Add` & then select `New Filter`. Name this filter `shaders`. Lastly, right click the `shaders` filter, hover over `Add` & select `Existing Item`. In the popup window, navigate to both of the `LoadShaders` files & select them.

#### OpenGL
It should not be necessary to install OpenGL, since it comes preinstalled on Windows, MacOS & Linux. However, if there are issues with OpenGL drivers, the [OpenGL Getting Started](https://www.khronos.org/opengl/wiki/Getting_Started) page will direct to the appropriate graphics driver sites.

In order to use OpenGL, you must ensure that Visual Studio can locate OpenGL on your computer & therefore you must add it as an additional dependency. In Visual Studio, right click your project file, select `Properties`, unfold `Linker`, select `Input` & edit `Additional Dependencies` by adding `opengl32.lib`.

#### Linking
Library & include files that will be downloaded in this lab will need to be placed in a new subfolder in the `C:\Users\Public` directory. Create a folder in this directory named `OpenGL` & inside this folder create two folders named `include` & `lib`.

Your Visual Studio project's linker needs to know the locations of the library files that are going to be downloaded. The include files will be located at `C:\Users\Public\OpenGL\include` & the library files will be located at `C:\Users\Public\OpenGL\lib`. In order to link to these locations, go to your Visual Studio project, navigate to the `Solution Explorer`, right click the project file, select `Properties`, unfold `Configuration Properties` & select `VC++ Properties`. Add the include directory `C:\Users\Public\OpenGL\include` to the `Include Directories` section & add the library directory `C:\Users\Public\OpenGL\lib` to the `Library Directories` section respectively.

### Libraries
#### GLFW
##### Overview
The GLFW library provides the ability to use OpenGL to render to windows, to receive input & also provides other useful events. In order to acquire GLFW, navigate to the [GLFW Download Page](https://www.glfw.org/download.html) & download the Windows pre-compiled 64-bit binaries.

##### Extraction
Open a file explorer & navigate to `C:\Users\Public\OpenGL` & open a second file explorer & navigate to the GLFW folder in the `Downloads` folder. In the GLFW folder, open the `include` subfolder & move the `GLFW` subfolder within that into the `include` folder in the `OpenGL` directory. In the GLFW folder in the `Downloads` folder, many `lib-vc` folders exist. These are library folders that correspond to different versions of Visual C++. Open the `lib-vc2022` folder & move all the files into the `lib` folder in the `OpenGL` directory.

In Visual Studio, right click your project file, select `Properties`, unfold `Linker`, select `Input` & edit `Additional Dependencies` by adding `glfw3.lib`. Lastly, in your main.cpp file, insert the ```#include <GLFW/glfw3.h>``` include. If Visual Studio fails to retrieve `glfw3.h`, then something has gone wrong in any of the aforementioned processes.

#### OpenGL Extension Wrangler Library (GLEW)
##### Overview
GLEW is an extension loading library. It provides checks to determine what extensions are able to be supported on any particular targeted platform. To download it, go to the [GLEW Download Page](https://glew.sourceforge.net/) & select the GLEW Binaries for Windows 32-bit & 64-bit. After this, you will be redirected to another site where you will have to wait a few seconds for your download to start.

##### Extraction
Once you have downloaded GLEW, navigate to your `Downloads` folder. Open the `include` folder & move the `GL` folder into your `C:\Users\Public\OpenGL\include` directory. Additionally, in the GLEW folder, navigate to the `Release/x64` folder & move the files into the `C:\Users\Public\OpenGL\lib` directory. Then, in the GLEW folder, navigate to `bin/Release/x64` & move the `glew32.dll` file into your Visual Studio project's directory where your `main.cpp` file is located.

In Visual Studio, right click your project file, select `Properties`, unfold `Linker`, select `Input` & edit `Additional Dependencies` by adding `glew32.lib` & `glew32s.lib`. Lastly, in your Visual Studio Project's main.cpp file, add the ```#include <GL/glew.h>``` include. In this instance, make sure that the ```#include``` is located above all other OpenGL related includes, since GLEW must run before all other OpenGL related libraries. If Visual Studio fails to retrieve `glew.h`, then something has gone wrong in any of the aforementioned processes.

#### GLAD Alternative to GLEW
##### Overview
In the [LearnOpenGL](https://learnopengl.com/Introduction) tutorial, the GLAD library is used as opposed to GLEW. If you are following the LearnOpenGL material, **you may wish to use GLAD, however I do not recommend this** either way, since this will require one to follow LearnOpenGL's error-prone system of implementing GLSL shaders into projects, which are needed at a basic level in this module & as the focus of the COMP3015 module. The `LoadShaders` header & cpp files in [Files](/Lab5/Files/) use GLEW & will allow for easier implementing of GLSL shaders. If you still wish to use GLAD, the process of retrieval is still available below.

##### Retrieval
GLAD can be downloaded from the [GLAD Loader-Generator Web Service](https://glad.dav1d.de/) in multiple different forms depending upon the individual's requirements. If one is to use GLAD for this lab, set the `Language` to `C++`, the `gl` to an OpenGL version of at least `Version 3.3` & lastly set the `Profile` to `Core`.

In the `Downloads` folder, open the `glad` folder & navigate to the `include` subfolder. Move both the internal `glad` & `KHR` folders to the `C:\Users\Public\OpenGL\include` folder. Then, in the `glad` folder's `lib` folder, move the `glad.c` file into your Visual Studio Project's project directory where your `main.cpp` file is located.

In your `main.cpp` file, add the ```//#include <glad/glad.h>``` include. Like with GLEW, make sure that the ```#include``` is located above all other OpenGL related includes, since GLAD must run before all other OpenGL related libraries. If Visual Studio fails to retrieve `glad.h`, then something has gone wrong in any of the aforementioned processes.

#### OpenGL Mathematics (GLM)
The GLM library provides extended mathematics for OpenGL. GLM's functions also follow the same naming conventions & functionality as GLSL. While GLM is specifically intended for use with OpenGL, it is also able to be utilised with other third parties.

Navigate to the [GLM Repository](https://github.com/g-truc/glm) & download the latest release in zip format. In the `Downloads` folder, open the `glm` folder & move the internal `glm` folder to the `C:\Users\Public\OpenGL\include` include directory. No glm ```#include``` directives are needed in your Visual Studio project for this lab. It will be specified as to whether you require them in future labs.

## Initialisation
### Window
#### GLFW
In order to begin, a window must be instantiated. Since GLFW will be used for this, it must be initialised with `glfwInit()`. Then, to instantiate a window, the ```GLFWwindow``` object is initialised with the `glfwCreateWindow()` constructor. The dimensions in the following example are 1280x720 & the name of the window is `Lab5`. The fourth parameter specifies which monitor to fullscreen on & the last parameter specifies which window's context to share resources with. These last two parameters can be kept as `NULL`. ```window``` is then checked to see if it has been successfully instantiated & if so ```glfwMakeContextCurrent()``` is called to bind OpenGL to the window:

**CPP**
```c++
//STD
#include <iostream>

//GLEW
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

using namespace std;

int main()
{
	//Initialisation of GLFW
    glfwInit();
	//Initialisation of 'GLFWwindow' object
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5", NULL, NULL);

	//Checks if window has been successfully instantiated
    if (window == NULL)
    {
        cout << "GLFW Window did not instantiate\n";
        glfwTerminate();
        return -1;
    }

	//Binds OpenGL to window
    glfwMakeContextCurrent(window);

    return 0;
}
```

#### GLEW
In order to render to the newly instantiated window, we need to set the GLEW viewport dimensions within the window. To do this, GLEW must first be initialised with the ```glewInit()``` function. Next, the viewport dimensions can be defined with the ```glViewport()``` function; the first two parameters specify the position of the window & the last two parameters specify the dimensions:

**CPP**
```c++
//Initialisation of GLEW
glewInit();

//Sets the viewport size within the window to match the window size of 1280x720
glViewport(0, 0, 1280, 720);
```

#### Dynamic Window Dimensions
The window's rendering dimensions currently cannot be modified during runtime, which means expanding & contracting the window will produce odd results. In order to allow for dynamic adjustment, the function ```framebuffer_size_callback()``` needs to be created. After this, the function needs to be set as the callback for the GLFW window resizing event with the ```glfwSetFramebufferSizeCallback()``` function. The first parameter is the window & the second is the function to call on a window resize:

**Header**
```c++
#pragma once

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>

//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
```

**CPP main()**
```c++
//Sets the framebuffer_size_callback() function as the callback for the window resizing event
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

**CPP framebuffer_size_callback()**
```c++
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Resizes window based on contemporary width & height values
    glViewport(0, 0, width, height);
}
```

### Render Loop
In order to prevent the program from closing immediately & to allow for perpetual rendering, we need to create the render loop. In order to do this, we check if the window is set to close with the ```glfwWindowShouldClose() function```. This becomes true when the ```x``` button at the top right of the window is clicked.

Inside of the render loop, the ```glfwSwapBuffers()``` function is called in order to perpetually swap the colour buffer being rendered to the window. The colour buffer is a 2-dimensional buffer that contains colour values per pixel for the window it is dedicated to rendering to. The ```glfwPollEvents()``` function queries for whether any GLFW events have been triggered, such as the ```framebuffer_size_callback()``` function.

Lastly, once the render loop is exited, the ```glfwTerminate()``` function is called in order to terminate GLFW safely:

**CPP**
```c++
//Render loop
while (glfwWindowShouldClose(window) == false)
{
	glfwSwapBuffers(window); //Swaps the colour buffer
	glfwPollEvents(); //Queries all GLFW events
}

//Safely terminates GLFW
glfwTerminate();
```

### Input
In order to take & process user input, we need to create a ```ProcessUserInput()``` function. This function needs to take in a ```GLFWwindow``` object pointer in order to acquire the input that was applied to said window. The ```glfwGetKey()``` function can be used to check if a key was interacted with within a window's context. We want to check if a key was pressed with ```GLFW_PRESS``` & that the key in question is the escape key, so in this case we check for ```GLFW_KEY_ESCAPE```. In order to perpetually check for user input, the ```ProcessUserInput()``` function needs to be called within the render loop:


**Header**
```c++
//Processes user input on a particular window
void ProcessUserInput(GLFWwindow* WindowIn);
```

**CPP main()**
```c++
//Render loop
while (glfwWindowShouldClose(window) == false)
{
	//Input
    ProcessUserInput(window); //Takes user input

	//Refreshing
    glfwSwapBuffers(window); //Swaps the colour buffer
    glfwPollEvents(); //Queries all GLFW events
}
```

**CPP processInput()**
```c++
void ProcessUserInput(GLFWwindow* WindowIn)
{
    //Closes window on 'exit' key press
	if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(WindowIn, true);
	}
}
```

### Rendering
We are able to render a colour to the window by clearing the window's colour buffer & setting a default colour. In order to do this, within the render loop we need to first call the ```glClearColor()``` function in order to specify the colour to default to. The parameters are RGBA; red, green, blue & alpha. For clarification on what 'alpha' refers to, that is transparency, so a value of ```1.0f``` would set the screen to be entirely opaque. Lastly, the ```glClear()``` functions must be called in order to clear a specific window buffer. We need to clear the colour buffer, so the function's parameter needs to be set to ```GL_COLOR_BUFFER_BIT```:

**CPP**
```c++
//Render loop
while (glfwWindowShouldClose(window) == false)
{
    //Input
    ProcessUserInput(window); //Takes user input

    //Rendering
    glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
    glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

    //Refreshing
    glfwSwapBuffers(window); //Swaps the colour buffer
    glfwPollEvents(); //Queries all GLFW events
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