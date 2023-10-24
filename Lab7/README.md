# Lab 7 - Transformations
## Overview
If you followed [Lab 5](/Lab5/README.md) as intended, you will have acquired the OpenGL Mathematics library (GLM). This library's classes, functions & types are designed to mirror or at least follow the conventions of GLSL for ease of use. This library is going to be used a lot in this section since it deals with transformations. The tasks in this lab require the following includes in ```main.cpp``` & set ```glm``` as an additional namespace to ```std```:

**CPP**
```c++
//GLM
#include "glm/ext/vector_float3.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
```

## Matrices
### Overview
To start with, we are going to rotate our wooden square in our scene on its side. In order to do this, we can create a 4x4 matrix with GLM's ```mat4``` type. We are going to call this variable ```transform```. We can use GLM's maths functions, such as ```rotate()```, in order to manipulate the values inside of the transform matrix.

### Rotation & Scale
The ```rotate()``` function's first parameter takes the matrix itself, the second parameter takes the degrees of rotation & the last parameter takes the direction in which to rotate; a 3x1 vector of x, y & z values. We are also going to use the ```scale()``` function to downsize the transform matrix to 50% on all axes, therefore we provide values of ```0.5```. Lastly in order to make use of the transform matrix, we need to set it as a uniform so that we can access it in our vertex shader:

**CPP**
```c++
//Instantiation of matrix
mat4 transform = mat4(1.0f);
//Rotate by 90 degrees on Z axis
transform = rotate(transform, radians(90.f), vec3(0.0, 0.0, 1.0));
//Downscale by 50%
transform = scale(transform, vec3(0.5, 0.5, 0.5));

//Setting of transformation values to uniform for vertex shader
GLint transformIndex = glGetUniformLocation(program, "transformIn");
glUniformMatrix4fv(transformIndex, 1, GL_FALSE, value_ptr(transform));
```

### Vertex Shader
Since we are going to be manipulating the position of our wooden square, we are going to be modifying our vertex shader, as opposed to our fragment shader. In order to achieve this, we need to declare our ```transformIn``` uniform & multiply it by our position vector when setting our final position to ```gl_Position```:

**GLSL**
```GLSL
//Transformation
uniform mat4 transformIn;

void main()
{
    //Transformation applied to vertices
    gl_Position = transformIn * vec4(position.x, position.y, position.z, 1.0);
    //Sending texture coordinates to next stage
    textureCoordinatesFrag = textureCoordinatesVertex;
}
```

## Task 1
Try composing the aforementioned code in order to rotate & downscale the rectangle.

## Dynamic Rotation
Next, we are going to get our wooden rectangle to perpetually rotate. First, we should make our transform variable global:

**CPP Globals**
```c++
//Transformations
mat4 transform;
```

All the transformation code from the last section needs to be relocated to the inside of the render loop. However, the rotation value needs to be perpetually changed. An easy way to do this is to use the ```glfwGetTime()``` function, which counts up from 0 upon the initialisation of GLFW. This is what we are going to set our degrees to rotate our rectangle to in the ```rotate()``` function:

**CPP Render Loop**
```c++
//Render loop
while (glfwWindowShouldClose(window) == false)
{
    //Input
    ProcessUserInput(window); //Takes user input

    //Rendering
    glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
    glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

    //Transformations
    transform = mat4(1.0f);
    transform = rotate(transform, (float)glfwGetTime(), vec3(0.0, 0.0, 1.0));
    transform = scale(transform, vec3(0.5, 0.5, 0.5));
    GLint transformIndex = glGetUniformLocation(program, "transformIn");
    glUniformMatrix4fv(transformIndex, 1, GL_FALSE, value_ptr(transform));

    //Drawing
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAOs[0]); //Bind buffer object to render; VAOs[0]
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Refreshing
    glfwSwapBuffers(window); //Swaps the colour buffer
    glfwPollEvents(); //Queries all GLFW events
}
```

## Task 2
Try composing the aforementioned code in order to perpetually rotate the downscaled the rectangle.

## Model View Projection (MVP)
### Model & View
In order to create a dynamically adjustable & realistic perception within a scene, we need to create a model-view-projection matrix (MVP). The model consists of the location of all objects within world space & the view determines the rotation of these objects within world space. Note that the viewer itself does not change position; instead, the world itself moves around the viewer.

### Initialisation
Once we have initialised our model matrix, we are going to use the ```scale()``` function to enlargen its contents. In doing so, this gives the impression that we are 'zooming in' or 'moving forwards.' we also use the ```rotate()``` function in order to move the scene downwards so as to create the impression that we have moved up above it. Lastly, we also use the ```translate()``` function to move the contents of the model so as to make it look as though we have moved backwards:

**CPP**
```c++
//Model matrix
mat4 model = mat4(1.0f);
//model = mat4(1.0f);
//Scaling to zoom in
model = scale(model, vec3(2.0f, 2.0f, 2.0f));
//Rotation to look down
model = rotate(model, radians(-45.0f), vec3(1.0f, 0.0f, 0.0f));
//Movement to position further back
model = translate(model, vec3(0.0f, 1.f, -1.5f));

//View matrix
mat4 view = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 1.0f, 0.0f));
```

### Projection
The projection component of the MVP represents the field of view/vision (FOV) displayed on the window & everything contained in it. There are two options for types of projection that we can use, orthographic & perspective. Orthographic projection is relatively simple, as it allows everything within the given field of vision to be viewed at its absolute size. However, when we observe the universe, the further away an object is, the smaller it appears. In order to achieve this effect, we need to use the more complex perspective form of projection.

### Initialisation
When initialising our projection matrix with perspective, we need to use the ```perspective()``` function. First, we need to supply the viewing angle for our FOV, which we are going to set to ```45.0f``` as degrees with the ```radians()``` function. Then, we need to give the window's width divided by its height. Lastly, we need to set the values for how close & how far objects in the scene may be allowed to be viewed within our FOV. In our case, any vertices at a position below / that are closer than ```0.1f``` & any vertices beyond ```100.f``` won't be rendered. Since our MVP is now complete, we also need to set it as a uniform for our vertex shader to make use of it, which we are going to call ```mvpIn```:

**CPP**
```c++
//Projection matrix
mat4 projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

// Model-view-projection matrix uniform for vertex shader
mat4 mvp = projection * view * model;
int mvpLoc = glGetUniformLocation(program, "mvpIn");
glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));
```

### Vertex Shader
**GLSL**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Texture coordinates from last stage
layout (location = 1) in vec2 textureCoordinatesVertex;

//Texture coordinates to send
out vec2 textureCoordinatesFrag;

//Model-View-Projection Matrix
uniform mat4 mvpIn;

void main()
{
    //Transformation applied to vertices
    gl_Position = mvpIn * vec4(position.x, position.y, position.z, 1.0);
    //Sending texture coordinates to next stage
    textureCoordinatesFrag = textureCoordinatesVertex;
}
```

### Task 3
Complete above.

### Task 4
Achieve the same transform in 'Dynamic Rotation' with addition of MVP.

## Controls
### Movement
#### Globals
**CPP**
```c++
//Transformations
//Relative position within world space
vec3 cameraPosition = vec3(0.0f, 0.0f, 3.0f);
//The direction of travel
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
//Up position within world space
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

//Time
//Time change
float deltaTime = 0.0f;
//Last value of time change
float lastFrame = 0.0f;
```

#### Model & Projection
Like before, but without mvp at this stage

**CPP**
```c++
//Model matrix
mat4 model = mat4(1.0f);
//Scaling to zoom in
model = scale(model, vec3(2.0f, 2.0f, 2.0f));
//Rotation to look down
model = rotate(model, radians(-45.0f), vec3(1.0f, 0.0f, 0.0f));
//Movement to position further back
model = translate(model, vec3(0.0f, 1.f, -1.5f));

//Projection matrix
mat4 projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
```

#### Render Loop
mat4 view: Sets the position of the viewer, the movement direction in relation to it & the world up direction

**CPP**
```c++
//Render loop
while (glfwWindowShouldClose(window) == false)
{
    //Time
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    //Input
    ProcessUserInput(window); //Takes user input

    //Rendering
    glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
    glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

    //Transformations
    mat4 view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    mat4 mvp = projection * view * model;
    int mvpLoc = glGetUniformLocation(program, "mvpIn");

    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));

    //Drawing
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAOs[0]); //Bind buffer object to render; VAOs[0]
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //Refreshing
    glfwSwapBuffers(window); //Swaps the colour buffer
    glfwPollEvents(); //Queries all GLFW events
}
```

#### User Input

**CPP**
```c++
void ProcessUserInput(GLFWwindow* WindowIn)
{
    //Closes window on 'exit' key press
    if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(WindowIn, true);
    }

    //Extent to which to move in one instance
    const float movementSpeed = 1.0f * deltaTime;
    //WASD controls
    if (glfwGetKey(WindowIn, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += movementSpeed * cameraFront;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= movementSpeed * cameraFront;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -= normalize(cross(cameraFront, cameraUp)) * movementSpeed;
    }
    if (glfwGetKey(WindowIn, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition += normalize(cross(cameraFront, cameraUp)) * movementSpeed;
    }
}
```
#### Task 5
Complete above.

### Direction
#### Overview
#### Globals
**CPP**
```c++
//Camera sidways rotation
float cameraYaw = -90.0f;
//Camera vertical rotation
float cameraPitch = 0.0f;
//Determines if first entry of mouse into window
bool mouseFirstEntry = true;
//Positions of camera from given last frame
float cameraLastXPos = 800.0f / 2.0f;
float cameraLastYPos = 600.0f / 2.0f;
```

#### Cursor
Added set input mode

**CPP**
```c++
GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Lab5", NULL, NULL);

//Checks if window has been successfully instantiated
if (window == NULL)
{
    cout << "GLFW Window did not instantiate\n";
    glfwTerminate();
    return -1;
}

//Sets cursor to automatically bind to window & hides cursor pointer
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//Binds OpenGL to window
glfwMakeContextCurrent(window);

//Initialisation of GLEW
glewInit();
```

#### Mouse Movement
**Header**
```c++
//Called on mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
```

**CPP**
```c++
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //Initially no last positions, so sets last positions to current positions
    if (mouseFirstEntry)
    {
        cameraLastXPos = (float)xpos;
        cameraLastYPos = (float)ypos;
        mouseFirstEntry = false;
    }

    //Sets values for change in position since last frame to current frame
    float xOffset = (float)xpos - cameraLastXPos;
    float yOffset = cameraLastYPos - (float)ypos;

    //Sets last positions to current positions for next frame
    cameraLastXPos = (float)xpos;
    cameraLastYPos = (float)ypos;

    //Moderates the change in position based on sensitivity value
    const float sensitivity = 0.025f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    //Adjusts yaw & pitch values against changes in positions
    cameraYaw += xOffset;
    cameraPitch += yOffset;

    //Prevents turning up & down beyond 90 degrees to look backwards
    if (cameraPitch > 89.0f)
    {
        cameraPitch = 89.0f;
    }
    else if (cameraPitch < -89.0f)
    {
        cameraPitch = -89.0f;
    }

    //Modification of direction vector based on mouse turning
    vec3 direction;
    direction.x = cos(radians(cameraYaw)) * cos(radians(cameraPitch));
    direction.y = sin(radians(cameraPitch));
    direction.z = sin(radians(cameraYaw)) * cos(radians(cameraPitch));
    cameraFront = normalize(direction);
}
```
#### Mouse Callback
**CPP**
```c++
//Sets the framebuffer_size_callback() function as the callback for the window resizing event
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//Sets the mouse_callback() function as the callback for the mouse movement event
glfwSetCursorPosCallback(window, mouse_callback);
```

#### Task 6
Complete above.