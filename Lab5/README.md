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
### Overview
From a high level perspective, there are 3 stages that must take place in order to render objects in 3D space to a window.
- The instantiation of spacial information in C++ | CPU
- The transition of data from the CPU to the GPU with OpenGL | CPU -->> GPU
- The rendering stage with GLSL (OpenGL Shading Language) | GPU

### CPU Instantiation
First, we must instantiate any coordinates in C++ that will ultimately be rendered to a window in some form. These coordinates must be contained within floating point arrays. For this reason, at this stage it is ambiguous as to what these coordinates relate to. Their purpose is only defined upon being converted into vertex buffer objects (VBOs). The coordinates in question could be manifested as the vertices of an object, its colours or other things. To keep things simple, we are only going to be instantiating the vertices at this stage:

**CPP**

Below ```glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);``` vv
```c++
float vertices[] = {
	-0.5f, -0.5f, 0.0f, //pos 0 | x, y, z
	0.5f, -0.5f, 0.0f, //pos 1
	0.0f, 0.5f, 0.0f //pos 2
};
```
Above ```while (glfwWindowShouldClose(window) == false)``` ^^

### CPU-GPU Conversion
#### Vertex Buffer Objects
The vertices array is currently mapped to CPU memory, as opposed to GPU memory. For this reason, we need to convert the vertices array into OpenGL vertex buffer objects (VBOs) so that they can be sent to the GPU. VBOs are able to store a large number of vertices, which allows for a significant amount of data to be sent to the GPU at once. This is beneficial as this reduces the relatively significant bottleneck of transitioning CPU memory to GPU memory.

First, a VBO must be created & assigned a buffer index with the ```glGenBuffers()``` function. Next, the ```glBindBuffer()``` function must be called in order to determine what buffer to assign the VBO to. In this case, we want to assign it to the ```GL_ARRAY_BUFFER```, since this is the buffer that contains vertices, as opposed say to colours. Then, we need to allocate memory for the vertices that we have sent to the VBO, which we do with the ```glBufferData()``` function:

**CPP**
```c++
//Declaration of index of VBO
unsigned int vertexBufferObject;
//Sets index of VBO
glGenBuffers(1, &vertexBufferObject);
//Binds VBO to array buffer for drawing vertices
glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
//Allocates buffer memory for the vertices
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

Lastly, we need to give our vertex shader on the GPU access to the VBO. In order to do this, we need to assign memory for a vertex attribute pointer on the GPU with the ```glVertexAttribPointer()``` function. There are many parameters that this function needs to take:
- #1: Vertex attribute index
- #2: Vertex attribute size, which equates to the size of one element of the vertices array
- #3: Type of data, so a float
- #4: Whether to normalise the data; this can be useful for integers, but not for floats
- #5: The stride, which determines the space between each vertex attribute; in our case the size of 3 floating point numbers
- #6: The offset of where the coordinate data should begin in the buffer; position 0 is the start of the VBO

**CPP**
```c++
//Allocates vertex attribute memory for vertex shader
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//Index of vertex attribute for vertex shader
glEnableVertexAttribArray(0);
```

#### Vertex Array Objects
Like VBOs, vertex array objects (VAOs) can be bound to an OpenGL buffer. VAOs are arrays of vertex attributes. For this reason, they can be used to store related vertex arrays & therefore are able to contain all the spacial information related to one object. For example, a VAO could contain a vertex attribute array for an object's coordinates, as well as another for its colours.

The benefit of using VAOs is that you only need to bind to one of them when setting up multiple vertex attribute arrays. A VBO is only able to contain one vertex attribute array.

**CPP Globals**
```c++
//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//Buffer objects
GLuint Buffers[NumBuffers];
```

The setup process for VAOs is similar to VBOs. First, we call ```glGenVertexArrays()``` in order to setup the VAO. Next, we call the ```glBindVertexArray()``` function to bind the VAO to OpenGL & lastly we index our buffer objects against our buffer wit hthe ```glGenBuffers()``` function.

In order to setup the desired VBO within our VAO, we have to call ```glBindBuffer()``` & in this case access the ```Triangles``` buffer object. Then, like before we allocate memory to the VBO based on the vertices array, setup our vertex attribute array & lastly unbind our VAO & VBO:

**CPP main()**
```c++
//Sets index of VAO
glGenVertexArrays(NumVAOs, VAOs);
//Binds VAO to a buffer
glBindVertexArray(VAOs[0]);
//Sets indexes of all required buffer objects
glGenBuffers(NumBuffers, Buffers);

//Binds VAO to array buffer
glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
//Allocates buffer memory for the vertices
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//Allocates vertex attribute memory for vertex shader
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//Index of vertex attribute for vertex shader
glEnableVertexAttribArray(0);

//Unbinding
glBindVertexArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
```

#### Shader Retrieval
In order to render our attribute arrays to a window, we need to send them through the OpenGL Graphics Pipeline. Depending upon the stage in the pipeline, we ourselves either cannot implement, have the option to, or must implement how the rendering is achieved. The stages that we need to implement are the vertex & fragment shaders.

In order to do this, we need to create two files, which we will place inside the `shaders` folder & Visual Studio `shaders` filter. They will be named `vertexShader.vert` & `fragmentShader.frag`, however the names & extensions can be anything.

The code below is placed during the OpenGL initialisation process in the ```main()``` function. Its purpose is to retrieve the shaders that we wish to implement, set them up with the ```LoadShaders()``` function & lastly activate them with the ```glUseProgram()``` function:

**CPP Globals & Includes**
```c++
#include "LoadShaders.h"

GLuint program;
```

**CPP main()**

Below ```glewInit();``` vv
```c++
//Load shaders
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

### GPU
#### Overview
Shaders do not run serially as most code would on a CPU. Instead, many instances of them run in parallel on the GPU. However, while each instance of a particular type of shader shares the same logic, they do not necessarily share the same values. Each shader running on the GPU is responsible for one component of a stage of the rendering process.

Open our vertex shader. Shaders are written in GLSL, the syntax of which is based on the C programming language, therefore also baring a resemblance to C++. Note that Visual Studio does not support GLSL syntax highlighting by default, however there are extensions for this. Regardless, it is easy to install GLSL syntax highlighting extensions within Visual Studio Code, so it may be beneficial to use Visual Studio Code for GLSL.

#### Vertex Shader
The vertex shader determines all the positions of the vertices of an object. Therefore, each instance of a running vertex shader correspondents to one particular vertice. To get started, first we should specify our GLSL version at the top of the file.

Notice the type of our variable ```position```. The ```layout``` qualifier allows for a variable's value to be either retrieved from the stage coming before (as with the use of ```in```), or to be sent to the stage coming after (with the use of ```out```). This can be done throughout the graphics pipeline's stages that we have access to. However, since the vertex shader is the first stage of the pipeline, we are also able to retrieve code from the CPU, as this comes directly before the vertex shader runs. This is what we are doing in this instance.

The ```location``` determines an index for our vertex shader variable ```position``` that an equivalent vertex attribute variable generated on the CPU is expected to match. The index is 0, as we set the vertex attribute index to be 0 as the first parameter of the ```glVertexAttribPointer()``` function in [Vertex Buffer Objects](#vertex-buffer-objects). Lastly, ```vec3``` is the actual type of the variable, which is a 3-dimensional vector:

**Globals**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
```

We need a ```main()``` function within the vertex shader in order to automatically allow the shader to be run. The ```gl_Position``` variable is predefined & is used to set the shader's output. This is automatically sent to the next stage of the graphics pipeline. The input we need to give ```gl_Position``` is the ```position``` variable's x, y & z values. An alpha value is also necessary for transparency. We are going to be rendering an opaque triangle, so we need to set the value to ```1.0```:

**main()**
```GLSL
void main()
{
    //Triangle vertices sent through gl_Position to next stage
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
```

#### Fragment Shader
The fragment shader is responsible for mapping the correct colours to the correct pixels. Therefore, each instance of a running fragment shader is responsible for one pixel & its specific colour.

In order to make use of the fragment shader, we need to create a variable named ```FragColor```. This variable will be outputted to the next stage of the graphics pipeline, therefore we need to specify ```out``` behind it. The next stage will expect it to contain four float values, therefore we need its type to be ```vec4```. Within the ```main()``` function, we are simply going to specify our RGBA values. The colour set in the code below should create a white triangle:

**fragmentShader.vert**
```GLSL
#version 460
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
```

Lastly, in our `main.cpp` file, we need to call two functions within the render loop in order to state that we wish to draw to the window. The first function is the ```glBindVertexArray()``` function, which determines which vertex array we wish to bind to & therefore are able to draw. In order to draw our triangle, we call the ```glDrawArrays()``` function. We specify ```GL_TRIANGLES``` so that our vertices are able to connect & for a surface to be drawn within them. For example, as opposed to a wireframe. The next parameter is the starting index & the last parameter is the amount of vertices to render. Make sure that the last parameter is set to at least the amount we need to render.

```c++
//Render loop
while (glfwWindowShouldClose(window) == false)
{
    //Input
    ProcessUserInput(window); //Takes user input

    //Rendering
    glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
    glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

    glBindVertexArray(VAOs[0]); //Bind buffer object to render
    glDrawArrays(GL_TRIANGLES, 0, 3); //Render buffer object

    //Refreshing
    glfwSwapBuffers(window); //Swaps the colour buffer
    glfwPollEvents(); //Queries all GLFW events
}
```

Now, you should be able to run your program & an indigo background with a white triangle should appear!