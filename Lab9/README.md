# Lab 9 - Model Loading
## Setup
[CMake](https://cmake.org/download/)

[ASSIMP](https://github.com/assimp/assimp/blob/master/Build.md)

[Rock](https://www.turbosquid.com/3d-models/rock07base3ds-3d-1899446)

[GLAD](/Lab5/README.md)

[Mesh](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/mesh.h#L4)

[Model](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/model.h#L26)

[Shader](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/shader.h#L4)

[Shader M](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/shader_m.h#L4)

- Clone ASSIMP source
- Install CMAKE
- Compile ASSIMP binaries in CMAKE
- Run ASSIMP VS project in Release
- Copy `C:\Users\Public\ASSIMP\Binaries\bin\Release\assimp-vc143-mt.dll` to OpenGL VS project

- VC++ Directories
    - Include Directories
        - C:\Users\Public\ASSIMP\Source\assimp\include
        - C:\Users\Public\ASSIMP\Binaries\include
    - Library Directories
        - C:\Users\Public\ASSIMP\Binaries\lib\Release
- Linker, Input, Additional Dependencies
    - assimp-vc143-mt.lib

- Acquire mesh, model, shader & shader_m header files from LearnOpenGL repo
    - Create LearnOpenGL includes folder for shader & shader_m files
    - Add mesh & model files to VS project

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