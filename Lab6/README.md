# Lab 6 - Lighting & Extras
## Indices
### Overview
All vertices in an OpenGL object are drawn as triangles. Therefore, any object that is made up of more than three points is always composed of multiple triangles. For example, one rectangle would be made up of two triangles that connect together.

This system presents a problem, since a rectangle on face value is made up of four points, whereas using two triangles to form a rectangle requires six points. This is not efficient, since duplicated vertices need to be stored & rendered. As an object acquires more vertices, this inefficiency becomes exponential & will result in bad performance. In order to get around this problem however, OpenGl supports a concept named indexed drawing.

### Indexing
Indexed drawing makes use of two arrays, for vertices & indices respectively. The vertices array must only contain unique points; that is, points that are not at the same position as any other in the array. The indices array then specifies the order in which to draw these points. This gets around the problem, since any vertice can now be called upon multiple times. Below, the vertices of four corners of a rectangle are displayed, as well as the indices for directing the order in which to draw them:

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
The indices array still needs to be bound to a buffer. The name of the object that takes indices as input is known as an element buffer object (EBO). When binding our indices to an EBO, we do still need to bind our vertices to a VBO as well. To bind to an EBO, we have to access the ```GL_ELEMENT_ARRAY_BUFFER``` as opposed to the ```GL_ARRAY_BUFFER```.

Notably, indices themselves are not drawn, since they only direct the drawing order. For this reason, they do not need to be assigned to a vertex attribute array. Therefore, we still only need to assign one vertex attribute array for our vertices:

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
glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
//Allocates buffer memory for the vertices of the 'Triangles' buffer
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//Binding & allocation for indices
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
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

### Render Loop
Inside the render loop, as opposed to calling ```glDrawArrays()``` we need to call ```glDrawElements()``` in order to direct the drawing process from the indices as opposed to the vertices directly:

**CPP**
```c++
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

### Task 1
Try composing the aforementioned code in order to generate a rectangle.

## Colours
### Coordinates
When supporting colours for our objects, we are able to specify colours in RGBA format for each vertex of an object. The colours themselves can be included within the vertices array as demonstrated below. For simplicity, we are not going to specify transparency/alpha (the 'A' in 'RGBA') here:

**CPP**
```c++
float vertices[] = {
//positions             //colours
0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f, //top right
0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f, //bottom right
-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, //bottom left
-0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f //top left
};
```

### Vertex Attribute Arrays
Unlike indices, the colour vertices do need to be applied within the drawing process. Therefore, we need to add a second vertex attribute array for colours & give it a second index. When doing this, we also need to modify the vertex attribute array for the positions of the object. This is because the addition of colours to the vertices array remaps the memory, therefore changing how the vertex attribute array needs to retrieve the data. For this reason, we give both vertex attribute arrays a spacing of ```6 * sizeof(float)``` & the second vertex attribute array the starting position of ```(void*)(3 * sizeof(float))```:

**CPP**
```c++
//Allocation & indexing of vertex attribute memory for vertex shader
//Positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Colours
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);
```

### Vertex Shader
Since we specified a vertex attribute array for colours, we need to create a new layout variable in the vertex shader. We are going to call this variable ```vertexColour``` & give it an index of 1, since its corresponding vertex attribute array was indexed at 1. Next, we are going to set ```fragColour``` as the value of ```vertexColour``` in order to pass the colour data for use in the fragment shader:

**GLSL**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Triangle colour
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

### Fragment Shader
In the fragment shader, we simply need to set the fragment shader's outgoing ```FragColor``` variable to the value of the incoming ```fragColour``` variable in order to set the colour. However, since we didn't specify any transparency/alpha values, we need to set one. Therefore, we need to wrap ```fragColour``` into a ```vec4``` - a vector of four values:

**GLSL**
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

### Task 2
Try composing the aforementioned code in order to generate a coloured rectangle.

## Uniforms
### Overview
Normally, when passing data through the graphics pipeline, it is sent through its various stages in a sequential, linearly order. Therefore, it can only be accessed by each stage one after the other. However, it is also possible to send data in such a way so that all stages of the graphics pipeline always have access to it & do not need to pass it from one stage to the next. These variables are known as uniforms. However, there are a few things that must be known about them first before they are used:
- Can roughly be described as a shader 'global' variable, since they are never localised to any particular stage of the graphics pipeline / any particular shader
- Become constants within the context of existing within the graphics pipeline; they can only be modified outside of it
- The mechanism for accessing them is not as fast as accessing vertex attribute arrays; therefore use vertex attribute arrays as opposed to uniforms where possible

### Initialisation
In order to create a uniform, we need to call the ```glGetUniformLocation()``` function upon a ```GLint``` variable in order to link it to a uniform variable within our GLSL program. In order to do this, we need to pass the shader's program in order to link to it, as well as the name of the uniform variable to link to specifically. For now we will assume its name as ```colourIn``` & will declare it in the shader later. After this, we can call the ```glUniform4f()``` function in order to set the value of ```colourLocation```, as well as ```colourIn``` within our shader, respectively:

**CPP**
```c++
//Gets index of colourIn uniform variable
GLint colourLocation = glGetUniformLocation(program, "colourIn");
//Sets colourIn
glUniform4f(colourLocation, 1.0f, 0.25f, 0.0f, 1.0f);
```

Since we are sending our colour data with a uniform variable, we no longer require our colour data within the vertices array. In addition, we also only need a single vertex attribute array since we are no longer sending it as a vertex attribute to the GPU:

**CPP**
```c++
float vertices[] = {
    //positions
    0.5f, 0.5f, 0.0f,   //top right
    0.5f, -0.5f, 0.0f,  //bottom right
    -0.5f, -0.5f, 0.0f, //bottom left
    -0.5f, 0.5f, 0.0f,  //top left
};

...

//Allocation & indexing of vertex attribute memory for vertex shader
//Positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

### Vertex Shader
We can remove all code within our vertex shader relating to colour. This is because our vertex shader does not render colour, nor does it need to pass any colour related data anymore since our colour uniform variable is accessible regardless:

**GLSL**
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

### Fragment Shader
Our fragment shader renders colour, therefore it needs to make use of our uniform variable. In order to give it overt access, we need to declare it as ```uniform vec4 colourIn```. Lastly, we can set ```FragColor``` to the value of ```colourIn```:

**GLSL**
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

### Task 3
Try composing the aforementioned code in order to generate a single-coloured rectangle with a uniform variable.

## Task ? (Dynamic Colour)

## Textures
In order to render textures, we will need an image loader. For this purpose, we are going to be using the [STB Image Loading Library](https://github.com/nothings/stb/blob/master/stb_image.h), which is comprised of a header file named ```stb_image.h```. In order to make use of it, download it from the link provided over the name & place it into your Visual Studio Project directory. After this, add it to the ```Source Files``` filter & add it as an included file to ```main.cpp```:

**CPP**
```c++
#include "stb_image.h"
```

You may notice that ```stb_image.h``` currently does not function. In order to implement it into your project properly, create a new CPP file, which we are going to call ```stbImageLoader.cpp``` & add the code displayed below to it. Note that there is no need to include the CPP file, only the header as aforementioned:

**CPP**
```c++
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

### Coordinates
Like with colours, we can implement coordinates into our vertices array. Textures are 2-dimensional & therefore only require two components to create a point, as opposed to three. Points given represent any particular normalised location within the texture's bounds. Therefore, the highest number we should use is ```1.0f``` & the lowest is ```0.0f```. Below, we access the points at the four corners of our texture. Lastly, also as with colours, we need to create a vertex attribute array for our texture coordinates:

**CPP**
```c++
float vertices[] = {
//Positions             //Textures
0.5f, 0.5f, 0.0f,       1.0f, 1.0f, //top right
0.5f, -0.5f, 0.0f,      1.0f, 0.0f, //bottom right
-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, //bottom left
-0.5f, 0.5f, 0.0f,      0.0f, 1.0f  //top left
};

unsigned int indices[] = {
    0, 1, 3, //first triangle
    1, 2, 3 //second triangle
};

...

//Allocation & indexing of vertex attribute memory for vertex shader
//Positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Textures
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
glEnableVertexAttribArray(1);
```

### Binding
We need to assign a buffer index & bind a texture to our ```GL_TEXTURE_2D``` buffer, as shown below:

**CPP**
```c++
//Textures to generate
glGenTextures(NumBuffers, Buffers);

//Binding texture to type 2D texture
glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);
```

### Wrapping
If a texture is applied to only part of an object as opposed to its entirety, there are multiple modes by which the texture can be displayed depending upon the desired result. This can be done with the ```glTexParameteri()``` function. Here are a list of options that one can use:

- ```GL_CLAMP_TO_BORDER``` prevents the texture from overspilling
- ```GL_CLAMP_TO_EDGE``` allows the edge pixels to continuously overspill
- ```GL_REPEAT``` allows the texture to repeatedly render itself adjacently
- ```GL_MIRRORED_REPEAT``` accomplishes ```GL_REPEAT``` while also flipping textures in the given direction of their given adjacent texture

These parameters can be applied specifically to the x & y axis of a texture, as opposed to needing to be identical on both axes. ```GL_TEXTURE_WRAP_S``` & ```GL_TEXTURE_WRAP_T``` correspond to the x & y axes respectively. We also need to specify our texture buffer, which is ```GL_TEXTURE_2D```:

**CPP**
```c++
//Selects x axis (S) of texture bound to GL_TEXTURE_2D & sets to repeat beyond normalised coordinates
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//Selects y axis (T) equivalently
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
```

### Data Retrieval
The texture we are using is the `woodPlanks.jpg` file located in the [media Folder](/Lab6/media/woodPlanks.jpg). Either create your own media folder, or take the existing one in this repository & put it into your Visual Studio Project directory. Note, there is no need to add the media folder as a filter in Visual Studio for the sake of textures.

Next, in order to retrieve our texture, we need to call ```stbi_load()```. We must provide the texture name & variables to store the texture's attributes: Width, height & the colour channels:

**CPP**
```c++
//Parameters that will be sent & set based on retrieved texture
int width, height, colourChannels;
//Retrieves texture data
unsigned char* data = stbi_load("media/woodPlanks.jpg", &width, &height, &colourChannels, 0);
```

### Generation
If our texture is retrieved successfully, we need to generate a texture from our loaded data with the ```glTexImage2D()``` function. There are many parameters, which are detailed below:
- #1: The texture buffer, in order to apply the texture data to the bound texture object
- #2: The mipmap level, which can either be set upon the texture or generated later; we are not going to set it yet, so we'll provide ```0```
- #3: The resulting image's colour format
- #4: The x dimension of the texture
- #5: The y dimension of the texture
- #6: Legacy feature which is always set to ```0```
- #7: The source image's colour format
- #8: The form of data in which we stored the image
- #9: The image data

While we do not have any mipmaps, we need to specify this regardless with the ```glGenerateMipmap()``` function. The parameter is the ```GL_TEXTURE_2D``` buffer:

**CPP**
```c++
if (data) //If retrieval successful
{
    //Generation of texture from retrieved texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //Automatically generates all required mipmaps on bound texture
    glGenerateMipmap(GL_TEXTURE_2D);
}
else //If retrieval unsuccessful
{
    cout << "Failed to load texture.\n";
    return -1;
}

//Clears retrieved texture from memory
stbi_image_free(data);
```

### Rendering
In order for OpenGL to know which texture to render, we need to call the ```glBindTexture()``` function in the render loop. We provide the ```GL_TEXTURE_2D``` buffer, as well as the index of the texture in the buffer:

**CPP**
```GLSL
//Drawing
glBindTexture(GL_TEXTURE_2D, Buffers[Textures]);
glBindVertexArray(VAOs[0]); //Bind buffer object to render; VAOs[0]
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

### Vertex Shader
Since we setup a vertex attribute array for our texture coordinates, we need to create a corresponding layout variable in the vertex shader. We are going to call this ```textureCoordinatesVertex```. Then we need to pass its value to a variable that we are going to name ```textureCoordinatesFrag``` in order to give our fragment shader access to it:

**GLSL**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Texture coordinates from last stage
layout (location = 1) in vec2 textureCoordinatesVertex;

//Texture coordinates to send
out vec2 textureCoordinatesFrag;

void main()
{
    //Triangle vertices sent through gl_Position to next stage
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    //Sending texture coordinates to next stage
    textureCoordinatesFrag = textureCoordinatesVertex;
}
```
### Fragment Shader
We need to create our input variable ```textureCoordinatesFrag``` in order to receive our image coordinate data from the past stages of the graphics pipeline. We also need a uniform variable of type ```sampler2D``` called textureIn in order to store the texture's colour data. In this scenario, we do not actually need to create a uniform variable in our ```main.cpp``` file, as this is done automatically. Lastly, we need to provide our texture to ```FragColor``` with the ```texture()``` function. This function maps the colour data of ```textureIn``` against the positional data of ```textureCoordinatesFrag```:

**GLSL**
```GLSL
#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Texture coordinates from last stage
in vec2 textureCoordinatesFrag;
//Texture (colours)
uniform sampler2D textureIn;

void main()
{
    //Setting of texture & its coordinates as colour map
    FragColor = texture(textureIn, textureCoordinatesFrag);
}
```

### Task 4
Try composing the aforementioned code in order to generate a textured rectangle.

### Scaling
#### Filtering
Currently, depending upon the size of the rendered rectangle, you may notice that the resolution is too low. However, OpenGL supports texture filtering for these situations. The filtering option for a texture can be set with the ```glTexParameteri()``` function. The first parameter specifies the buffer type, the second parameter specifies whether to apply the filtering option for downscaling or for upscaling specifically & the last parameter specifies the type of filtering to use.

```GL_TEXTURE_MIN_FILTER``` is for downscaling & therefore setting this to use an upscaling filtering system will not work. For this reason, we can set it to use ```GL_NEAREST```, which achieves nearest neighbour filtering. This form of filtering simply enlargens the image.

```GL_TEXTURE_MAG_FILTER``` is for upscaling & therefore we have the option of setting the filtering option to be ```GL_LINEAR```. This form of filtering interpolates existing data points in order to generate adjacent ones around them that share similarities to those they originate from. This creates a blur effect:

**CPP**
```c++
//Sets bound texture to use nearest neighbour downscaling
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//Sets to use linear interpolation upscaling
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

### Task 5
Try composing the aforementioned code in order to generate a textured rectangle with potentially more appropriate filtering.

#### Mipmaps
When an object is downscaled significantly, such as a scenario where it is being viewed from far away in a scene, unwanted visual artifacts may appear. This is because OpenGL will not be able to differentiate between notable features & details of a texture & so will try to represent them all based on their relative positions. This is also not efficient, since a texture may be being rendered at a significantly lower resolution to that of its actual resolution.

In order to deal with this issue, mipmaps can be used. Mipmaps are a collection of textures that represent different resolutions of the same image. Depending upon the scaling of the texture / the distance of the texture being viewed in a scene, a different mipmap level will be selected.

OpenGL will generate mipmaps for us, therefore we don't have to create them manually, such as in an image editing program. However, between mipmaps we may still want to interpolate our texture. Therefore, we can use the ```GL_LINEAR_MIPMAP_LINEAR``` setting in the ```glTexParameteri()``` function when downscaling. Of course, this is not necessary when upscaling, so we can continue to use ```GL_LINEAR``` in that regard:

```c++
//Sets to use linear interpolation between adjacent mipmaps
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//Sets to use linear interpolation upscaling (past largest mipmap texture)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

### Task 6
Try composing the aforementioned code in order to generate a textured rectangle with mipmap filtering.