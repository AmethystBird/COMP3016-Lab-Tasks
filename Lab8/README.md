# Lab 8 - Procedural Terrain Generation
## Terrain
### Includes
**CPP**
```c++
//STD
#include <iostream>
#include <vector>

//GLEW
#include <GL/glew.h>

//GLM
#include "glm/ext/vector_float3.hpp"
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr

//GENERAL
#include "main.h"
#include "LoadShaders.h"

//SPECIALISED
#include "FastNoiseLite.h"
```

### Globals
**CPP**
```c++
#define RENDER_DISTANCE 128 //Render width of map
#define MAP_SIZE RENDER_DISTANCE * RENDER_DISTANCE //Size of map in x & z space

//Amount of chunks across one dimension
const int squaresRow = RENDER_DISTANCE - 1;
//Amount of chunks on map
const int squaresGrid = squaresRow * squaresRow;
//Two triangles per square to form a 1x1 chunk
const int trianglesPerSquare = 2;

//Amount of triangles across one dimension
const int trianglesRow = squaresRow * trianglesPerSquare;
//Amount of triangles on map
const int trianglesGrid = trianglesRow * squaresRow;
```

### Vertices
**CPP**
```c++
//Generation of height map vertices
GLfloat terrainVertices[MAP_SIZE][6];

//Positions to start drawing from
float drawingStartPosition = 1.0f;
float columnVerticesOffset = drawingStartPosition;
float rowVerticesOffset = drawingStartPosition;

int rowIndex = 0;
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
    //vertices
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
**CPP**
```c++
//Looking straight forward
model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
//Elevation to look upon terrain
model = translate(model, vec3(0.0f, -2.f, -1.5f));
```

### Render Loop
**CPP**
```c++
glDrawElements(GL_TRIANGLES, MAP_SIZE * 32, GL_UNSIGNED_INT, 0);
```

### Vertex Shader
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
**CPP**
```c++
#include "FastNoiseLite.h"
```

### Noise
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

//Initialising height map
vector<float> terrainHeightMap(MAP_SIZE);
```

### Height Variation
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
Removal of terrainVertices height at [i][1].

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

## Biomes
### Cellular Noise
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
Removal of colour setting.

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

### Altitude
**CPP**
```c++
//Determination of biomes based on height
if (terrainVertices[i][1] >= (0.5f / 8.0f))
{
    //Snow
    terrainVertices[i][3] = 1.0f;
    terrainVertices[i][4] = 1.0f;
    terrainVertices[i][5] = 1.0f;
}
```