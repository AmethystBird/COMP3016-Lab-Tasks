# Lab 9 - Model Loading
## Overview
In order to load models in OpenGL, we will need to modify our project's dependencies. First, we will need to retrieve the ASSIMP model loading library in order to load models from files. However, constructing models in OpenGL from these files requires a significant amount of extra code. Luckily, we are able to acquire dependencies for this purpose from [LearnOpenGL](). Lastly, we will be using GLAD instead of GLEW due to LearnOpenGL's dependencies upon it.

## Setup
### CMake
In order to make use of ASSIMP, one can download it in a precompiled binary form. However, it is not guaranteed that this form of retrieval will always work on all systems. For this reason, we are going to download ASSIMP's source & compile the binaries. In order to do this, we need to install [CMake](https://cmake.org/download/). For Windows, the appropriate file to download is the `Windows x64 Installer`:

![Image]()

### ASSIMP
We need to clone the ASSIMP repository in order to acquire its source. We can do this anywhere, however a good location for this is within our `Public` directory, so as to place it adjacently to our `OpenGL` dependencies for good organisation. Navigate to `C:\Users\Public` & create a folder named `ASSIMP` & create two folders within this one called `Source` & `Binaries`:

![Image]()

Open the `Build.md` file within the [ASSIMP Github repository](https://github.com/assimp/assimp/blob/master/Build.md) & navigate to the `Get the source` section under `Manual build instructions`. A command for cloning the ASSIMP repository should be provided:

![Image]()

Either clone the repository through the command line as specified by ASSIMP's instructions, or alternatively one can use software such as Github Desktop. The location for where we are going to clone it is `C:\Users\Public\ASSIMP\Source`.

### Building ASSIMP
In order to build ASSIMP, we need to first open CMake. Within CMake, two text boxes should be located at the top left of its main window. The text box labeled `Where is the source code` will require the directory to ASSIMP's source. The text box labeled `Where to build the binaries` instead requires the directory to build the binaries to:

![CMake](/Lab9/media/CMake.png)

Once our source code & the building locations are provided, we can configure our build with the `Configure` button at the bottom left of the CMake window. A new window should pop up, giving options for what kind of generator we wish to use. We probably need to select `Visual Studio 17 2022`, since we are going to be using ASSIMP with Visual Studio. If you are using a different version of Visual Studio, then select the appropriate version for your system. We also need to ensure that we build 64 bit ASSIMP binaries, therefore we need to choose the `x64` option. Once both of these specifications are selected, select `Finish`. Once this is done, CMake will start building the binaries.

![CMakeConfiguration](/Lab9/media/CMakeConfigure.png)

Once the binaries have been built, we still need to generate the Visual Studio ASSIMP files. In order to do this, click the `Generate` button next to the `Configure` button. Now, a Visual Studio project called `Assimp.sln` should have been created within `C:\Users\Public\ASSIMP\Binaries`. Open this project & build it. When doing so, make sure to do so with the `x64` configuration & preferably in `Release` mode. Note that **we are not using the Assimp.sln Visual Studio project for implementing this lab's OpenGL code**. It is only being used for generating Visual Studio project files for your respective OpenGL project.

A file called `assimp-vc143-mt.dll` should now be located in `C:\Users\Public\ASSIMP\Binaries\bin\Release\`. Copy this file into your OpenGL Visual Studio project.

ASSIMP's directories should be in the following locations:
- Includes
    - Code: `C:\Users\Public\ASSIMP\Source\assimp\include\assimp`
    - Configuration: `C:\Users\Public\ASSIMP\Binaries\include\assimp`
- Libraries
    - `C:\Users\Public\ASSIMP\Binaries\lib\Release`

We need to add these include & library paths to our Visual Studio project. In order to do this, right click the project in the `Solution Explorer`, click `Properties`, unfold `Configuration Properties` & select `VC++ Directories`.

Add the following to the `Include Directories`:
- `C:\Users\Public\ASSIMP\Source\assimp\include`
- `C:\Users\Public\ASSIMP\Binaries\include`

Add the following to the `Library Directories`:
- `C:\Users\Public\ASSIMP\Binaries\lib\Release`

Next, we also need to link the ASSIMP library to the Visual Studio project. In order to do this, unfold `Linker` & navigate to `Input` & add `assimp-vc143-mt.dll` under `Additional Dependencies`.

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
- Create LearnOpenGL includes folder for all files

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