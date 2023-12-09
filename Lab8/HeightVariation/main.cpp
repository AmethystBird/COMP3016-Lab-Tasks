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

//SPECIALISED
#include "FastNoiseLite.h"

using namespace std;
using namespace glm;

//Window
int windowWidth;
int windowHeight;

//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//Buffer objects
GLuint Buffers[NumBuffers];

//Transformations
//Relative position within world space
vec3 cameraPosition = vec3(0.0f, 0.0f, 3.0f);
//The direction of travel
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
//Up position within world space
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

//Camera sidways rotation
float cameraYaw = -90.0f;
//Camera vertical rotation
float cameraPitch = 0.0f;
//Determines if first entry of mouse into window
bool mouseFirstEntry = true;
//Positions of camera from given last frame
float cameraLastXPos = 800.0f / 2.0f;
float cameraLastYPos = 600.0f / 2.0f;

//Time
//Time change
float deltaTime = 0.0f;
//Last value of time change
float lastFrame = 0.0f;

#define RENDER_DISTANCE 128 //Render width of map
#define MAP_SIZE RENDER_DISTANCE * RENDER_DISTANCE //Size of map in x & z space

//Amount of chunks across one dimension
const int squaresRow = RENDER_DISTANCE - 1;
//Two triangles per square to form a 1x1 chunk
const int trianglesPerSquare = 2;
//Amount of triangles on map
const int trianglesGrid = squaresRow * squaresRow * trianglesPerSquare;

int main()
{
    //Initialisation of GLFW
    glfwInit();
    //Initialisation of 'GLFWwindow' object
    windowWidth = 1280;
    windowHeight = 720;
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

    //Load shaders
    ShaderInfo shaders[] =
    {
        { GL_VERTEX_SHADER, "shaders/vertexShader.vert" },
        { GL_FRAGMENT_SHADER, "shaders/fragmentShader.frag" },
        { GL_NONE, NULL }
    };

    program = LoadShaders(shaders);
    glUseProgram(program);

    //Sets the viewport size within the window to match the window size of 1280x720
    glViewport(0, 0, 1280, 720);

    //Sets the framebuffer_size_callback() function as the callback for the window resizing event
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Sets the mouse_callback() function as the callback for the mouse movement event
    glfwSetCursorPosCallback(window, mouse_callback);

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

    //Generation of height map vertices
    GLfloat terrainVertices[MAP_SIZE][6];

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

    //Positions to start drawing from
    float drawingStartPosition = 1.0f;
    float columnVerticesOffset = drawingStartPosition;
    float rowVerticesOffset = drawingStartPosition;

    int rowIndex = 0;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        //Generation of x & z vertices for horizontal plane
        terrainVertices[i][0] = columnVerticesOffset;
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

    //Sets index of VAO
    glGenVertexArrays(NumVAOs, VAOs);
    //Binds VAO to a buffer
    glBindVertexArray(VAOs[0]);
    //Sets indexes of all required buffer objects
    glGenBuffers(NumBuffers, Buffers);
    //glGenBuffers(1, &EBO);

    //Binds vertex object to array buffer
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
    //Allocates buffer memory for the vertices of the 'Triangles' buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(terrainVertices), terrainVertices, GL_STATIC_DRAW);

    //Binding & allocation for indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(terrainIndices), terrainIndices, GL_STATIC_DRAW);

    //Allocation & indexing of vertex attribute memory for vertex shader
    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Model matrix
    mat4 model = mat4(1.0f);
    //Scaling to zoom in
    model = scale(model, vec3(2.0f, 2.0f, 2.0f));
    //Looking straight forward
    model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    //Elevation to look upon terrain
    model = translate(model, vec3(0.0f, -2.f, -1.5f));

    //Projection matrix
    mat4 projection = perspective(radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

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
        mat4 view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp); //Sets the position of the viewer, the movement direction in relation to it & the world up direction
        mat4 mvp = projection * view * model;
        int mvpLoc = glGetUniformLocation(program, "mvpIn");

        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, value_ptr(mvp));

        //Drawing
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, MAP_SIZE * 32, GL_UNSIGNED_INT, 0);

        //Refreshing
        glfwSwapBuffers(window); //Swaps the colour buffer
        glfwPollEvents(); //Queries all GLFW events
    }

    //Safely terminates GLFW
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Resizes window based on contemporary width & height values
    glViewport(0, 0, width, height);
}

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