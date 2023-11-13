# Lab 9 - Model Loading
## Setup
[CMake](https://cmake.org/download/)

[ASSIMP](https://github.com/assimp/assimp/blob/master/Build.md)

[Rock](https://www.turbosquid.com/3d-models/rock07base3ds-3d-1899446)

## Implementation
### Includes
**CPP**
```c++
//GLAD
//#include <GL/glew.h>
#include <glad/glad.h>

//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//LEARNOPENGL
#include <learnopengl/shader_m.h>
#include <learnopengl/model.h>
```

### GLAD
**CPP**
```c++
//Initialisation of GLAD
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    cout << "GLAD failed to initialise\n";
    return -1;
}
```

### File Retrieval
**CPP**
```c++
Shader Shaders("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
Model Rock("media/rock/Rock07-Base.obj");
Shaders.use();
```

### Render Loop
```c++
...
//Rendering
glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer
glClear(GL_DEPTH_BUFFER_BIT); //Might need

glEnable(GL_CULL_FACE); //Discards all back-facing triangles

//Transformations
mat4 view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp); //Sets the position of the viewer, the movement direction in relation to it & the world up direction
mat4 mvp = projection * view * model;
Shaders.setMat4("mvpIn", mvp); //Setting of uniform with Shader class

//Drawing
Rock.Draw(Shaders);
...
```