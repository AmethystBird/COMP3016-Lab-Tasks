# Lab 7 - Transformations
## Transformations
### Rotation
**CPP**
```c++
//GLM
#include "glm/ext/vector_float3.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
```

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
### Task 1
Complete above.

### Dynamic Rotation
**CPP Globals**
```c++
//Transformations
mat4 transform;
```

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

### Task 2
Complete above.

## Perspective
### Model View Projection (MVP)
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

//Projection matrix
mat4 projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

// Model-view-projection matrix uniform for vertex shader
mat4 mvp = projection * view * model;
int mvpLoc = glGetUniformLocation(program, "mvpIn");
glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));
```

**Vertex Shader**
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
Achieve the same transform in 'Dynamic Rotation' with addition of MVP. Fix solution using 'glm::' unnecessarily

### 3D Rotation
Might do, not sure yet

### Depth Buffer (Z Buffer)
If 3D rotation done

## Controls


### Movement
### Zooming