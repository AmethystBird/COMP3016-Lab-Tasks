# Lighting
## Continuation
### Indices
**CPP**
```c++
float vertices[] = {
0.5f, 0.5f, 0.0f, //top right
0.5f, -0.5f, 0.0f, //bottom right
-0.5f, -0.5f, 0.0f, //bottom left
-0.5f, 0.5f, 0.0f //top left
};

unsigned int indices[] = {
    0, 1, 3, //first triangle
    1, 2, 3 //second triangle
};
```

### Element Buffer Objects
**CPP**
```c++
//Sets index of VAO
glGenVertexArrays(NumVAOs, VAOs); //NumVAOs, VAOs
//Binds VAO to a buffer
glBindVertexArray(VAOs[0]); //VAOs[0]
//Sets indexes of all required buffer objects
glGenBuffers(NumBuffers, Buffers); //NumBuffers, Buffers
//glGenBuffers(1, &EBO);

//Binds vertex object to array buffer
glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]); //Buffers[Triangles]
//Allocates buffer memory for the vertices of the 'Triangles' buffer
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//Binding & allocation for indices
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]); //Buffers[Indices]
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//Allocates vertex attribute memory for vertex shader
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//Index of vertex attribute for vertex shader
glEnableVertexAttribArray(0);

//Unbinding
glBindVertexArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
```

## Colour Coordinates
**CPP Vertices**
```c++
float vertices[] = {
//positions             //colours
0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f, //top right
0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, //bottom right
-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, //bottom left
-0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f //top left
};
```

**CPP Vertex Attribute Arrays**
```c++
//Allocation & indexing of vertex attribute memory for vertex shader
//Positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Colours
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);
```

**Vertex Shader**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Triangle colours
layout (location = 1) in vec3 vertexColour;

//Colour output to fragment shader
out vec3 fragColour;

void main()
{
    //Triangle vertices sent through gl_Position to next stage
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    //Colour values sent to fragment shader
    fragColour = vertexColour;
}
```

**Fragment Shader**
```GLSL
#version 460
//Colour value to send to next stage
out vec4 FragColor;
//Colour value from last stage
in vec3 fragColour;

void main()
{
    //RGBA values
    FragColor = vec4(fragColour, 1.0f);
}
```

## Uniforms
[NOTE] must go after program is initialised

**CPP**
```c++
//Gets index of colourIn uniform variable
GLint colourLocation = glGetUniformLocation(program, "colourIn");
//Sets colourIn
glUniform4f(colourLocation, 1.0f, 0.25f, 0.0f, 1.0f);
```

**Vertex Shader**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;

void main()
{
    //Triangle vertices sent through gl_Position to next stage
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
```

**Fragment Shader**
```GLSL
#version 460
//Colour value to send to next stage
out vec4 FragColor;
//Colour value
uniform vec4 colourIn;

void main()
{
    //RGBA values
    FragColor = colourIn;
}
```

## Task 1 (Dynamic Colour)
## Textures
### STB Image
[STB Image Download](https://github.com/nothings/stb/blob/master/stb_image.h)

**stbImageLoader.cpp**
```c++
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

**main.cpp**
```c++
#include "stb_image.h"
```

### Initialisation


### Coordinates
### Wrapping
### Filtering
### Mipmaps
### Shader
### Texture Units