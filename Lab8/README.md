# Lab 8 - Procedural Terrain Generation
## Terrain
### Includes
For this lab, we are not going to be using textures, so you can safely remove includes relating to this. Later however, we are going to add an extra library for generating noise:

**CPP**
```c++
//STD
#include <iostream>

//GLEW
#include <GL/glew.h>

//GLM
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr

//GENERAL
#include "main.h"
#include "LoadShaders.h"
```

### Globals
In order to generate our terrain, we are first going to initialise some globals. Our first two are ```RENDER_DISTANCE``` & ```MAP_SIZE```. The value of ```RENDER_DISTANCE``` is the amount of chunks across either the x or y direction of the terrain. ```MAP_SIZE``` is the total number of chunks. To clarify on what chunks are, they are square representations of the terrain, rather than triangular. As a result, our chunks will be mapped within our indices array. In our case, we will be using 1x1 squares.

The variable ```squaresRow``` will later be used to check if an entire row of chunks has been generated. ```trianglesPerSquare``` effectively sets the size of the chunk. In our case, we want our chunks to be 1x1 squares. ```trianglesGrid``` contains the total amount of triangles within the terrain map. This will be used to initialise & to count through each triangle to generate chunks, or rather indices:

**CPP**
```c++
#define RENDER_DISTANCE 128 //Render width of map
#define MAP_SIZE RENDER_DISTANCE * RENDER_DISTANCE //Size of map in x & z space

//Amount of chunks across one dimension
const int squaresRow = RENDER_DISTANCE - 1;
//Two triangles per square to form a 1x1 chunk
const int trianglesPerSquare = 2;
//Amount of triangles on map
const int trianglesGrid = squaresRow * squaresRow * trianglesPerSquare;
```

### Vertices
When generating our terrain, we first need to create its vertices. In order to store them, we need a 2 dimensional array named ```terrainVertices```. The array's first dimension will store every triangle across the terrain grid, therefore we will set its size to ```MAP_SIZE```. The second dimension will allow each triangle to contain 6 values: 3 for points & 3 for colours.

Our variable ```drawingStartPosition``` sets the initial drawing position for the terrain. The column & row verticesOffset variables take its value initially, however their values are shifted in order to generate triangles in the correct locations within the terrain's grid. ```rowIndex``` will be used to check if an entire row of triangles has been generated & if so, the next row will begin generation:

**CPP**
```c++
//Generation of height map vertices
GLfloat terrainVertices[MAP_SIZE][6];

//Positions to start drawing from
float drawingStartPosition = 1.0f;
float columnVerticesOffset = drawingStartPosition;
float rowVerticesOffset = drawingStartPosition;

int rowIndex = 0;
```

Within the for loop shown, we are going to index across every triangle within the terrain grid. The first three indexes of ```terrainVertices``` will then be set. The x & z positions will take the values of the column & row verticesOffset variables respectively. This will allow the positions of each triangle to be perpetually shifted in order to generate the entire grid. For now, we will also keep setting the same green colour to each vertice.

In order to generate triangles along rows, our ```columnVerticesOffset``` variable is shifted in each iteration of the loop. In order to move down a row, ```rowIndex``` is checked against the length of a row (which happens to also be the length of a column) with the ```RENDER_DISTANCE``` variable. If this is true, the ```columnVerticesOffset``` variable is set back to its starting position with ```drawingStartPosition``` & ```rowVerticesOffset``` is shifted to the next row.

It is important to note however, that we are not yet generating the heightmap. Unlike the x & z values, the heightmap will later have non-uniform variation applied to it. In addition, you may have noticed that we are only generating one triangle per square. Because of this, no flipped triangles are being generated to slot into the second halves of each square. Generating both triangles is not necessary & the lack of whole squares will be amended for when we generate our chunks, otherwise known as indices:

**CPP**
```c++
for (int i = 0; i < MAP_SIZE; i++)
{
    //Generation of x & z vertices for horizontal plane
    terrainVertices[i][0] = columnVerticesOffset;
    terrainVertices[i][1] = 0.0f;
    terrainVertices[i][2] = rowVerticesOffset;

    //Colour
    terrainVertices[i][3] = 0.0f;
    terrainVertices[i][4] = 0.75f;
    terrainVertices[i][5] = 0.25f;

    //Shifts x position across for next triangle along grid
    columnVerticesOffset = columnVerticesOffset + -0.0625f;

    //Indexing of each chunk within row
    rowIndex++;
    //True when all triangles of the current row have been generated
    if (rowIndex == RENDER_DISTANCE)
    {
        //Resets for next row of triangles
        rowIndex = 0;
        //Resets x position for next row of triangles
        columnVerticesOffset = drawingStartPosition;
        //Shifts y position
        rowVerticesOffset = rowVerticesOffset + -0.0625f;
    }
}
```

### Indices
In order to map our vertices to chunks, we need to create our indices array, which we are going to call ```terrainIndices```. Like when filling our vertex array, we also need column & row indicesOffset variables. Our for loop for generating the chunks needs to index through every triangle we generated in our vertex array, therefore the for loop's condition takes ```trianglesGrid```.

Notice that we create two triangles in each iteration of the loop, which is necessary since one chunk comprises of two triangles. However, we didn't create the vertices for the adjacent triangles when generating the vertex array. The reason we are able to do this is because we are using the vertices from the side of the triangle in the given next iteration:

**CPP**
```c++
//Generation of height map indices
GLuint terrainIndices[trianglesGrid][3];

//Positions to start mapping indices from
int columnIndicesOffset = 0;
int rowIndicesOffset = 0;

//Generation of map indices in the form of chunks (1x1 right angle triangle squares)
rowIndex = 0;
for (int i = 0; i < trianglesGrid - 1; i += 2)
{
    terrainIndices[i][0] = columnIndicesOffset + rowIndicesOffset; //top left
    terrainIndices[i][2] = RENDER_DISTANCE + columnIndicesOffset + rowIndicesOffset; //bottom left
    terrainIndices[i][1] = 1 + columnIndicesOffset + rowIndicesOffset; //top right

    terrainIndices[i + 1][0] = 1 + columnIndicesOffset + rowIndicesOffset; //top right
    terrainIndices[i + 1][2] = RENDER_DISTANCE + columnIndicesOffset + rowIndicesOffset; //bottom left
    terrainIndices[i + 1][1] = 1 + RENDER_DISTANCE + columnIndicesOffset + rowIndicesOffset; //bottom right

    //Shifts x position across for next chunk along grid
    columnIndicesOffset = columnIndicesOffset + 1;

    //Indexing of each chunk within row
    rowIndex++;

    //True when all chunks of the current row have been generated
    if (rowIndex == squaresRow)
    {
        //Resets for next row of chunks
        rowIndex = 0;
        //Resets x position for next row of chunks
        columnIndicesOffset = 0;
        //Shifts y position
        rowIndicesOffset = rowIndicesOffset + RENDER_DISTANCE;
    }
}
```

### Vertex Attribute Pointers
Past labs will have resulted in vertex attribute arrays for vertices & texturing & for colours to be sent to the GPU as uniform variables. We are no longer using textures, however we are sending colours as vertex attribute arrays. Remove any redundant code relating to textures & uniform colours & implement the following:

**CPP**
```c++
//Allocation & indexing of vertex attribute memory for vertex shader
//Positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

//Colours
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```

### Model
Due to the orientation of our world, we need to adjust our model. Set the ```radians()``` to be ```0.0f``` so that we are facing straight forwards & set ```translate()``` ```vec3``` y value to ```-2.f``` so that we are higher up:

**CPP**
```c++
//Looking straight forward
model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
//Elevation to look upon terrain
model = translate(model, vec3(0.0f, -2.f, -1.5f));
```

### Render Loop
We need to increase the amount of indices that are able to be rendered when calling ```glDrawElements()``` to ```MAP_SIZE``` multiplied by ```32```:

**CPP**
```c++
glDrawElements(GL_TRIANGLES, MAP_SIZE * 32, GL_UNSIGNED_INT, 0);
```

### Vertex Shader
In order to retrieve colour in our vertex shader, we need to create a layout variable at the index of our colour vertex attribute array; we will call this ```colourVertex```. We will then send its value to ```colourFrag``` for use in our fragment shader:

**Shader**
```GLSL
#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;
//Colour coordinates from last stage
layout (location = 1) in vec3 colourVertex;

//Model-View-Projection Matrix
uniform mat4 mvpIn;

//Colour to send
out vec3 colourFrag;

void main()
{
    //Transformation applied to vertices
    gl_Position = mvpIn * vec4(position.x, position.y, position.z, 1.0);
    //Sending texture coordinates to next stage
    colourFrag = colourVertex;
}
```

### Fragment Shader
All we need to do in the fragment shader is set ```colourFrag```'s values to ```FragColor```, along with our value of ```1.0f``` in our ```vec4``` for opaqueness:

**Shader**
```GLSL
#version 460
//Colour value to send to next stage
out vec4 FragColor;

//Colour coordinates from last stage
in vec3 colourFrag;

void main()
{
    //Setting of colour coordinates to colour map
    FragColor = vec4(colourFrag, 1.0f);
}
```

### Task 1
Try composing the aforementioned code in order to generate a flat grid of chunks.

## Height Map
### Fast Noise Lite
Currently, our terrain is flat. We could use pseudo-randomisation in order to generate height variation, however this wouldn't look like natural terrain. In order to generate a more natural look, we can use noise. In order to do this, retrieval of the [Fast Noise Lite Header Library](https://github.com/Auburn/FastNoiseLite/blob/master/Cpp/FastNoiseLite.h) is required for this lab. Download the ```FastNoiseLite.h``` file, place it into your Visual Studio project's directory & add it as an existing item to your project. Lastly, include the file as shown below:

**CPP**
```c++
#include "FastNoiseLite.h"
```

### Noise
Before we generate our vertex array, we need to create an object of type ```FastNoiseLite```, which we are going to call ```TerrainNoise```. Fast Noise Lite supports multiple noise algorithms. For the terrain, we are going to be using Perlin noise, which we can set with the ```SetNoiseType()``` function. We can also set the scale of the noise with the ```SetFrequency()``` function & set the seed with the ```SetSeed()``` function:

**CPP**
```c++
//Assigning perlin noise type for map
FastNoiseLite TerrainNoise;
//Setting noise type to Perlin
TerrainNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
//Sets the noise scale
TerrainNoise.SetFrequency(0.05f);
//Generates a random seed between integers 0 & 100
int terrainSeed = rand() % 100;
//Sets seed for noise
TerrainNoise.SetSeed(terrainSeed);
```

### Height Variation
We need to apply Perlin noise values to every y value of our terrain's vertices. Notice that our terrain expands in both x & y directions, however our ```terrainVertices``` array stores each triangle linearly. If we applied 1-dimensional Perlin noise to our triangles, this would create strange results. This is because our terrain's x & y values will be rendered as a plane, so applying Perlin noise in 1 dimension would contradict the resulting 2-dimensional structure of the terrain's plane.

In order to apply our Perlin noise 2-dimensionally, we need to create a 2-deep nested for loop & supply noise values based on both our x & y index values to each height vertice in our ```terrainVertices``` array. This works because our array's data is ordered & therefore may as well be a 2-dimensional array:

**CPP**
```c++
//Terrain vertice index
int i = 0;
//Using x & y nested for loop in order to apply noise 2-dimensionally
for (int y = 0; y < RENDER_DISTANCE; y++)
{
    for (int x = 0; x < RENDER_DISTANCE; x++)
    {
        //Setting of height from 2D noise value at respective x & y coordinate
        terrainVertices[i][1] = TerrainNoise.GetNoise((float)x, (float)y);
        i++;
    }
}
```

### Vertices
Since we have set our height vertices in the heightmap nested loop, we shouldn't set our height vertices in our triangle generation for loop:

**CPP**
```c++
for (int i = 0; i < MAP_SIZE; i++)
{
    //Generation of x & z vertices for horizontal plane
    terrainVertices[i][0] = columnVerticesOffset;
    terrainVertices[i][2] = rowVerticesOffset;
    ...
}
```

### Task 2
Try composing the aforementioned code in order to generate natural-looking height variation across the grid of chunks.

## Biomes
### Cellular Noise
Currently, our terrain only has one biome. Since our biome appears green, we are going to consider it a plains biome. Much like with our heightmap, it is also possible to generate biomes with noise algorithms. We are going to generate a desert. In order to do this, we need to create a new ```FastNoiseLite``` object which we are going to call ```BiomeNoise```. While not necessary, we are going to use cellular noise as opposed to Perlin noise this time. Make sure to set a different seed with the ```biomeSeed``` variable. Using the same seed in certain cases can produce noticeable repetition between all the elements of our terrain's variation:

**CPP**
```c++
//Biome noise
FastNoiseLite BiomeNoise;
BiomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
BiomeNoise.SetFrequency(0.05f);
int biomeSeed = rand() % 100;
TerrainNoise.SetSeed(biomeSeed);
```

### Noise Generation Loop
In our nested loop for setting our height noise, we can also set our biome. We can determine biomes based on cut off values. This ensures that biomes form cohesive areas. In our case, noise values less than or the same as ```0.75f``` will generate our plains biome & values greater than this will generate our desert biome. We are going to display our biomes through different colour values: Plains biomes will be green & deserts will be yellow:

**CPP**
```c++
//Retrieval of biome to set
float biomeValue = BiomeNoise.GetNoise((float)x, (float)y);

if (biomeValue <= -0.75f) //Plains
{
    terrainVertices[i][3] = 0.0f;
    terrainVertices[i][4] = 0.75f;
    terrainVertices[i][5] = 0.25f;
}
else //Desert
{
    terrainVertices[i][3] = 1.0f;
    terrainVertices[i][4] = 1.0f;
    terrainVertices[i][5] = 0.5f;
}
```
### Vertices
Since we are setting colours within our noise generation nested loop, we need to remove the code in our vertices generation loop that sets the colours of vertices.

**CPP**
```c++
int rowIndex = 0;
for (int i = 0; i < MAP_SIZE; i++)
{
    //Generation of x & z vertices for horizontal plane
    terrainVertices[i][0] = columnVerticesOffset;
    terrainVertices[i][2] = rowVerticesOffset;

    //Shifts x position across for next triangle along grid
    columnVerticesOffset = columnVerticesOffset + -0.0625f;

    //Indexing of each chunk within row
    rowIndex++;
    //True when all triangles of the current row have been generated
    if (rowIndex == RENDER_DISTANCE)
    {
        //Resets for next row of triangles
        rowIndex = 0;
        //Resets x position for next row of triangles
        columnVerticesOffset = drawingStartPosition;
        //Shifts y position
        rowVerticesOffset = rowVerticesOffset + -0.0625f;
    }
}
```
### Task 3
Try composing the aforementioned code in order to generate natural-looking biomes across the terrain.

### Task 4
Try generating a snowy-mountain biome based on height level in which the colour of the vertices is set to white.

## Depth
While observing the scene, you may have noticed that depth of the terrain is difficult to conceptualise. This is because no lighting has been implemented in the scene, with the exception of simply setting colours. While not in the scope of COMP3016, [Basic lighting](https://learnopengl.com/Lighting/Basic-Lighting) will significantly improve the appearance of the terrain, as well as many other applications of OpenGL.