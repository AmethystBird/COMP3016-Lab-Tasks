# Lab 9 - Model Loading
## Overview
In order to load models in OpenGL, we will need to modify our project's dependencies. First, we will need to retrieve the Assimp model loading library in order to load models from files. However, constructing models in OpenGL from these files requires a significant amount of extra code. Luckily, we are able to acquire dependencies for this purpose from [LearnOpenGL](). Lastly, we will be using GLAD instead of GLEW due to LearnOpenGL's dependencies upon it.

## Setup
### CMake
In order to make use of Assimp, one can download it in a precompiled binary form. However, it is not guaranteed that this form of retrieval will always work on all systems. For this reason, we are going to download Assimp's source & compile the binaries. In order to do this, we need to install [CMake](https://cmake.org/download/). For Windows, the appropriate file to download is the `Windows x64 Installer`:

![CMake Download](/Lab9/media/CMakeDownload.png)

### Assimp
We need a location to store Assimp's source & our future binaries. This can be anywhere, however a good location for this is within our `Public` directory, so as to place it adjacently to our `OpenGL` dependencies for good organisation. Navigate to `C:\Users\Public` & create a folder named `Assimp` & create two folders within this one called `Source` & `Binaries`:

We need to clone the Assimp repository in order to acquire its source. Open the `Build.md` file within the [Assimp Github repository](https://github.com/assimp/assimp/blob/master/Build.md) & navigate to the `Get the source` section under `Manual build instructions`. A command for cloning the Assimp repository should be provided:

![Assimp Repository](/Lab9/media/AssimpRepository.png)

Either clone the repository through the command line as specified by Assimp's instructions, or alternatively one can use software such as Github Desktop. The location for where we are going to clone it is `C:\Users\Public\Assimp\Source`.

### Building Assimp with CMake
#### Directories
In order to build Assimp, we need to first open CMake. Within CMake, two text boxes should be located at the top left of its main window. The text box labeled `Where is the source code` will require the directory to Assimp's source. The text box labeled `Where to build the binaries` instead requires the directory to build the binaries to:

![CMake](/Lab9/media/CMake.png)

#### Configuration
Once our source code & the building locations are provided, we can configure our build with the `Configure` button at the bottom left of the CMake window. A new window should pop up, giving options for what kind of generator we wish to use. We probably need to select `Visual Studio 17 2022`, since we are going to be using Assimp with Visual Studio. If you are using a different version of Visual Studio, then select the appropriate version for your system. We also need to ensure that we build 64 bit Assimp binaries, therefore we need to choose the `x64` option. Once both of these specifications are selected, select `Finish`. Once this is done, CMake will start building the binaries.

![CMakeConfiguration](/Lab9/media/CMakeConfigure.png)

#### Generation
Once the binaries have been built, we still need to generate the Visual Studio Assimp files. In order to do this, click the `Generate` button next to the `Configure` button. Now, a Visual Studio project called `Assimp.sln` should have been created within `C:\Users\Public\Assimp\Binaries`. Open this project & build it. When doing so, make sure to do so with the `x64` configuration & preferably in `Release` mode. Note that **we are not using the Assimp.sln Visual Studio project for implementing this lab's OpenGL code**. It is only being used for generating Visual Studio project files to move into your respective Visual Studio OpenGL project.

A file called `assimp-vc143-mt.dll` should now be located in `C:\Users\Public\Assimp\Binaries\bin\Release\`. Copy this file into your OpenGL Visual Studio project.

### Visual Studio Project
#### VC++ Directories
Assimp's directories should be in the following locations shown below. The code files should mostly be made up of many header files, the configuration should be limited to one file named `config.h` & the libraries should consist of two files named `assimp-vc143-mt` with the file extensions `.exp` & `.lib`:

- **Include** Code: `C:\Users\Public\Assimp\Source\assimp\include\assimp`
- **Include** Configuration: `C:\Users\Public\Assimp\Binaries\include\assimp`
- **Library**: `C:\Users\Public\Assimp\Binaries\lib\Release`

We need to add these include & library paths to our Visual Studio project. In order to do this, right click the project in the `Solution Explorer`, click `Properties`, unfold `Configuration Properties` & select `VC++ Directories`. Add the following paths to the `Include` & `Library Directories`:

- **Include** Code: `C:\Users\Public\Assimp\Source\assimp\include`
- **Include** Configuration: `C:\Users\Public\Assimp\Binaries\include`
- **Library**: `C:\Users\Public\Assimp\Binaries\lib\Release`

Lastly, we need to add the Assimp includes to our `main.cpp` file. If this fails, then something in the aforementioned process was done incorrectly:

**CPP**
```c++
//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
```

#### Linking
Next, we also need to link the Assimp library to the Visual Studio project. In order to do this, unfold `Linker` & navigate to `Input` & add `assimp-vc143-mt.lib` under `Additional Dependencies`.

### LearnOpenGL
#### Files
Assimp allows us to retrieve models from files. However, it lacks the ability to construct the models. Therefore, we still need to map models to a form that OpenGL recognises. This task is significant & therefore we are going to use [LearnOpenGL's](https://learnopengl.com/Introduction) own model construction libraries for this purpose.

#### Acquisition
We are going to acquire the necessary files from LearnOpenGL's Github repository. There are four files we need, one half for constructing models & the other for loading shaders. The former files are [mesh.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/mesh.h#L4), [model.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/model.h#L26) & the latter are [shader.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/shader.h#L4) & [shader_m.h](https://github.com/JoeyDeVries/LearnOpenGL/blob/3e94252892660902bef62068c35253cbe3464c9b/includes/learnopengl/shader_m.h#L4).

#### Includes
Once the LearnOpenGL files have been retrieved, navigate to `C:\Users\Public\OpenGL\include` & create a new folder called `learnopengl`. Place all four files inside of this folder. Since the `learnopengl` folder is within the umbrella `OpenGL` folder, it should already be included within the Visual Studio project.

However, we still need to add the LearnOpenGL includes to our `main.cpp` file. If this fails, then something in the aforementioned process was done incorrectly, or it may be possible that the `OpenGL` include & library folder is not setup or included correctly as in past labs. In addition, since we are using LearnOpenGL's shader loader, we no longer need to include `LoadShaders.h`:

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

*"GLAD can be downloaded from the [GLAD Loader-Generator Web Service](https://glad.dav1d.de/) in multiple different forms depending upon the individual's requirements. ... set the `Language` to `C++`, the `gl` to an OpenGL version of at least `Version 3.3` & lastly set the `Profile` to `Core`.*

*In the `Downloads` folder, open the `glad` folder & navigate to the `include` subfolder. Move both the internal `glad` & `KHR` folders to the `C:\Users\Public\OpenGL\include` folder. Then, in the `glad` folder's `lib` folder, move the `glad.c` file into your Visual Studio Project's project directory where your `main.cpp` file is located.*

*In your `main.cpp` file, add the ```#include <glad/glad.h>``` include. Like with GLEW, make sure that the ```#include``` is located above all other OpenGL related includes, since GLAD must run before all other OpenGL related libraries. If Visual Studio fails to retrieve `glad.h`, then something has gone wrong in any of the aforementioned processes."*

### Rock Model
With all our code dependencies not setup, we still need to acquire a model that we can compose into our scene. We are going to use a free Rock `.obj` model from [Turbosquid](https://www.turbosquid.com/3d-models/rock07base3ds-3d-1899446). However you can find your own model if desired. For greater certainty in the model loading correctly, using a `.obj` file is preferable since this lab also uses this format:

![Turbosquid Rock](/Lab9/media/TurbosquidRock.png)

There are various options when downloading the rock model. We only need the `Rock07-Base-Obj` & `Rock07-BaseTextures` zip files. Once both are downloaded, decompress both zip files. Within our Visual Studio project, if the folder does not already exist, create one called `media` & create a folder called `rock` inside of it. Next, move all the textures from the `Rock07-BaseTextures` folder & both the mtl & obj `Rock07-Base` files within the `Rock07-Base-Obj` folder into the `rock` folder in your Visual Studio project.

## Implementation
### Initialisation
Where GLEW would normally be initialised, we are going to initialise GLAD instead. Additionally, we also need to replace our old shader loading code to use LearnOpenGL's shader loader. Lastly, we need to load our rock model by creating a `Model` object & providing the path to our rock `.obj` file:

**CPP**
```c++
//Initialisation of GLAD
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
    cout << "GLAD failed to initialise\n";
    return -1;
}

//Loading of shaders
Shader Shaders("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
Model Rock("media/rock/Rock07-Base.obj");
Shaders.use();
```

Note that we ourselves do not need to access our rock's vertices, nor do we manually send our rock through a buffer or setup vertex attribute arrays for its information. This is done automatically when we initialise our rock.

### Model
In the case of the rock model, its appearance will likely be huge in respect to our coordinate system model's previous scaling settings in past labs. By using a scale of ```0.025f``` on all axes, the rock should appear at an appropriate size:

**CPP**
```c++
//Scaling to zoom in
model = scale(model, vec3(0.025f, 0.025f, 0.025f));
```

### Render Loop
Within our render loop, we need to call ```glEnable(GL_CULL_FACE)``` in order to set any backwards facing vertices to be invisible. If we don't do this, then both the front & back faces of any 3D object in our scene are going to render, irrespective of the observer's position in relation to them. This will create strange visual artifacts.

We also need to change how we set our uniforms in order to not act against our new shader loader's way of setting up uniforms. We should only have one uniform, which is our ```mvp```. We can assign it as a uniform by calling ```Shaders.setMat4()``` & by passing the desired name of our uniform to use within our shaders, as well as our actual variable.

Lastly, we can remove our drawing code & replace it with our model's ```Draw()``` function & provide our shader program to it:

**CPP**
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

### Shaders
In our vertex shader, our vertex attribute pointer at location 2 needs to be set to ```textureVertex``` & sent through ```textureFrag``` so our fragment shader can process the texture. Then, in our fragment shader we need to set ```FragColor``` to our texture. In order to do this, we need to call the ```texture()``` function & pass two parameters. The first parameter requires the texture's colour & the second requires the texture's coordinates so that the texture's colours can be mapped correctly:

**Vertex Shader**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Texture coordinates from last stage
layout (location = 2) in vec2 textureVertex;

//Model-View-Projection Matrix
uniform mat4 mvpIn;

//Texture to send
out vec2 textureFrag;

void main()
{
    //Transformation applied to vertices
    gl_Position = mvpIn * vec4(position.x, position.y, position.z, 1.0);
    //Sending texture coordinates to next stage
    textureFrag = textureVertex;
}
```

**Fragment Shader**
```GLSL
#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Texture coordinates from last stage
in vec2 textureFrag;

uniform sampler2D texture_diffuse1;

void main()
{
    //Setting of colour coordinates to colour map
    FragColor = texture(texture_diffuse1, textureFrag);
}
```

### Task 1
Try to compose the aforementioned code in order to render a rock to the scene that is scaled appropriately.

## Second Model
### Setup
Now that we have rendered one object into the scene, we are going to add a second one. In order to do this, we are going to be introducing a [tree model](https://www.turbosquid.com/3d-models/yamaboushi-tan-6000-a-3d-model-1814882). As with downloading the rock, navigate to the tree download as displayed below & acquire both the tree's `obj` & `mtl` files from the `yamaboushi_tan_6000_a_obj.zip` file & its associated textures in the `tex.zip` file:

![Turbosquid Tree](/Lab9/media/TurbosquidTree.png)

Once both are downloaded, decompress both zip files. Within our Visual Studio project, create a folder called `tree` inside of the `media` folder. Next, move all the textures from the `tex` folder & both the `mtl` & `obj` `yamaboushi_tan_6000_a_spr1` files within the `yamaboushi_tan_6000_a_obj` folder into the `tree` folder in your Visual Studio project.

You likely noticed that there are multiple tree model variations & an overwhelming amount of textures as a result. Whether you are using the tree suggested above or not, if you wish to reduce the amount of textures in your `media` folder down to only the necessary ones, open the model's associated ```mtl``` file in a text editor for a list of textures that are utilised by the model.

### Implementation
#### Model-View-Projection Matrix
We will need to scale our tree model differently to our rock model. Because of this, we need to make use of the model-view-projection matrix. In order to scale, move or translate our tree model in any way, we need to translate our MVP in order to change our model's position in relation to it. Since this will now need to be done multiple times throughout the render loop, we are going to create a function for this purpose called ```SetMatrices()```:

**Header**
```c++
//Sets the model-view-projection matrix
void SetMatrices(Shader& ShaderProgramIn);
```

In order to facilitate ```SetMatrices()```, we need to elevate our MVP variables to object variables so that they can also be accessed by the function. Within the function, we need to move the code within our render loop that sets the value of our MVP & assigns the uniform value to it:

**CPP**
```c++
//Model-View-Projection Matrix
mat4 mvp;
mat4 model;
mat4 view;
mat4 projection;

...

void SetMatrices(Shader& ShaderProgramIn)
{
    mvp = projection * view * model; //Setting of MVP
    ShaderProgramIn.setMat4("mvpIn", mvp); //Setting of uniform with Shader class
}
```

Note that it is important to **replace old, local variable equivalents of our MVP variables that still exist with our new object variables** instead.

#### Draw Function
If we try to draw our tree now with the ```Draw()``` function, it should render on top of the rock. This is of course more desireable than our tree floating in the air somewhere else, so we are going to leave this as is. However, feel free to change the positions of any of the models yourself if you wish to.

#### Scale Function
Our problem is that the tree model is far larger than our rock, so we will need to scale down its size. In order to do this, we will need to downscale our model variable with the ```scale()``` function. Every time we change a component of our mvp, we also need to set our MVP in order to synchronise our values. In order to do this, we need to call ```SetMatrices()``` after every rescaling of our model, or after any kind of translation whatsoever.

#### Effect of Translation
It is important to understand that when we translate any component of our MVP, that it has a combined/relative effect, rather than a setting effect. As an example, this holds true for when we call ```scale()``` on our model variable. In order to reduce the size of our tree, executing ```scale()``` with decimal values reduces the model's size in relation to its hitherto (up until now) value by multiplication; it does not set our model's size to the value we give.

#### Loop Iterations
Because we are operating within our render loop, we also need to account for our model's values for the loop's next iteration. Because of this, after drawing our tree, we upscale our model variable back to our original position with values of `20.0f` & then call ```SetMatrices()``` once more. This will ensure that our rock is drawn at the correct size. We also need to call ```SetMatrices()``` after setting our view. Originally, this is the only location where we used to set our matrices:

**Render Loop**
```c++
//Transformations & Drawing
//Viewer orientation
view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp); //Sets the position of the viewer, the movement direction in relation to it & the world up direction

//Rock
SetMatrices(Shaders);
Rock.Draw(Shaders);

//Tree (changes MVP in relation to past values)
model = scale(model, vec3(0.05f, 0.05f, 0.05f));
SetMatrices(Shaders);
Tree.Draw(Shaders);

//Rock (reorient MVP back to starting values)
model = scale(model, vec3(20.0f, 20.0f, 20.0f));
SetMatrices(Shaders);
```

#### Task 2
Try to compose the aforementioned code in order to additionally render a tree to the scene, where both models are scaled appropriately.