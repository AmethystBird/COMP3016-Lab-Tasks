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

### Building ASSIMP with CMake
#### Overview
In order to build ASSIMP, we need to first open CMake. Within CMake, two text boxes should be located at the top left of its main window. The text box labeled `Where is the source code` will require the directory to ASSIMP's source. The text box labeled `Where to build the binaries` instead requires the directory to build the binaries to:

![CMake](/Lab9/media/CMake.png)

#### Configuration
Once our source code & the building locations are provided, we can configure our build with the `Configure` button at the bottom left of the CMake window. A new window should pop up, giving options for what kind of generator we wish to use. We probably need to select `Visual Studio 17 2022`, since we are going to be using ASSIMP with Visual Studio. If you are using a different version of Visual Studio, then select the appropriate version for your system. We also need to ensure that we build 64 bit ASSIMP binaries, therefore we need to choose the `x64` option. Once both of these specifications are selected, select `Finish`. Once this is done, CMake will start building the binaries.

![CMakeConfiguration](/Lab9/media/CMakeConfigure.png)

#### Generation
Once the binaries have been built, we still need to generate the Visual Studio ASSIMP files. In order to do this, click the `Generate` button next to the `Configure` button. Now, a Visual Studio project called `Assimp.sln` should have been created within `C:\Users\Public\ASSIMP\Binaries`. Open this project & build it. When doing so, make sure to do so with the `x64` configuration & preferably in `Release` mode. Note that **we are not using the Assimp.sln Visual Studio project for implementing this lab's OpenGL code**. It is only being used for generating Visual Studio project files for your respective OpenGL project.

A file called `assimp-vc143-mt.dll` should now be located in `C:\Users\Public\ASSIMP\Binaries\bin\Release\`. Copy this file into your OpenGL Visual Studio project.

### Visual Studio Project
#### VC++ Directories
ASSIMP's directories should be in the following locations shown below. The code files should mostly be made up of many header files, the configuration should be limited to one file named `config.h` & the libraries should consist of two files named `assimp-vc143-mt` with the file extensions `.exp` & `.lib`:

- **Include** Code: `C:\Users\Public\ASSIMP\Source\assimp\include\assimp`
- **Include** Configuration: `C:\Users\Public\ASSIMP\Binaries\include\assimp`
- **Library**: `C:\Users\Public\ASSIMP\Binaries\lib\Release`

We need to add these include & library paths to our Visual Studio project. In order to do this, right click the project in the `Solution Explorer`, click `Properties`, unfold `Configuration Properties` & select `VC++ Directories`. Add the following paths to the `Include` & `Library Directories`:

- **Include** Code: `C:\Users\Public\ASSIMP\Source\assimp\include`
- **Include** Configuration: `C:\Users\Public\ASSIMP\Binaries\include`
- **Library**: `C:\Users\Public\ASSIMP\Binaries\lib\Release`

Lastly, we need to add the ASSIMP includes to our `main.cpp` file. If this fails, then something in the aforementioned process was done incorrectly:

**CPP**
```c++
//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
```

#### Linking
Next, we also need to link the ASSIMP library to the Visual Studio project. In order to do this, unfold `Linker` & navigate to `Input` & add `assimp-vc143-mt.lib` under `Additional Dependencies`.

### LearnOpenGL
#### Files
ASSIMP allows us to retrieve models from files. However, it lacks the ability to construct the models. Therefore, we still need to map models to a form that OpenGL recognises. This task is significant & therefore we are going to use [LearnOpenGL's](https://learnopengl.com/Introduction) own model construction libraries for this purpose.

#### Acquisition
We are going to acquire the necessary files from LearnOpenGL's Github repository. There are four files we need, one half for constructing models & the other for loading shaders. The former files are [mesh.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/mesh.h#L4), [model.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/model.h#L26) & the latter are [shader.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/shader.h#L4) & [shader_m.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/shader_m.h#L4).

#### Includes
Once the LearnOpenGL files have been retrieved, navigate to `C:\Users\Public\OpenGL\include` & create a new folder called `learnopengl`. Place all four files inside of this folder. Since the `learnopengl` folder is within the umbrella `OpenGL` folder, it should already be included within the Visual Studio project.

However, we still need to add the LearnOpenGL includes to our `main.cpp` file. If this fails, then something in the aforementioned process was done incorrectly, or it may be possible that the `OpenGL` include & library folder is not setup or included correctly. In addition, since we are using LearnOpenGL's shader loader, we no longer need to include `LoadShaders.h`:

**CPP**
```c++
//LEARNOPENGL
#include <learnopengl/shader_m.h>
#include <learnopengl/model.h>
```

### GLAD
#### Includes
In order to make use of LearnOpenGL's libraries, we need to use GLAD instead of GLEW. We can replace our GLEW include in our `main.cpp` file by including `glad.h` instead:

**CPP**
```c++
//GLAD
#include <glad/glad.h>
```

#### Acquisition
Instructions on how to add GLAD to a Visual Studio project are included in [Lab 5](/Lab5/README.md) & are referenced below:

*"GLAD can be downloaded from the [GLAD Loader-Generator Web Service](https://glad.dav1d.de/) in multiple different forms depending upon the individual's requirements. If one is to use GLAD for this lab, set the `Language` to `C++`, the `gl` to an OpenGL version of at least `Version 3.3` & lastly set the `Profile` to `Core`.*

*In the `Downloads` folder, open the `glad` folder & navigate to the `include` subfolder. Move both the internal `glad` & `KHR` folders to the `C:\Users\Public\OpenGL\include` folder. Then, in the `glad` folder's `lib` folder, move the `glad.c` file into your Visual Studio Project's project directory where your `main.cpp` file is located.*

*In your `main.cpp` file, add the ```#include <glad/glad.h>``` include. Like with GLEW, make sure that the ```#include``` is located above all other OpenGL related includes, since GLAD must run before all other OpenGL related libraries. If Visual Studio fails to retrieve `glad.h`, then something has gone wrong in any of the aforementioned processes."*

### Rock Model
With all our code dependencies not setup, we still need to acquire a model that we can compose into our scene. We are going to use a free Rock `.obj` model from [Turbosquid](https://www.turbosquid.com/3d-models/rock07base3ds-3d-1899446). However you can find your own model if desired. For greater certainty in the model loading correctly, using a `.obj` file is preferable since this lab also uses this format:

![Turbosquid Rock]()

There are various options when downloading the rock model. We only need the `Rock07-Base-Obj` & `Rock07-BaseTextures` zip files. Once both are downloaded, decompress both zip files. Within our Visual Studio project, if the folder does not already exist, create one called `media` & create a folder called `rock` inside of it. Next, move all the textures from the `Rock07-BaseTextures` folder & both the mtl & obj `Rock07-Base` files within the `Rock07-Base-Obj` folder into the `rock` folder in your Visual Studio project.

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

- Setup GLAD
- Acquire mesh, model, shader & shader_m header files from LearnOpenGL repo
- Create LearnOpenGL includes folder for all files

## Implementation
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