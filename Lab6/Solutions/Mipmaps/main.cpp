//STD
#include <iostream>

//GLEW
#include <GL/glew.h>

//GENERAL
#include "main.h"
#include "LoadShaders.h"

//TEXTURING
#include "stb_image.h"


using namespace std;

//VAO vertex attribute positions in correspondence to vertex attribute type
enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//VAOs
GLuint VAOs[NumVAOs];

//Buffer types
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
//Buffer objects
GLuint Buffers[NumBuffers];


int main()
{
    //Initialisation of GLFW
    glfwInit();
    //Initialisation of 'GLFWwindow' object
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Lab5", NULL, NULL);

    //Checks if window has been successfully instantiated
    if (window == NULL)
    {
        cout << "GLFW Window did not instantiate\n";
        glfwTerminate();
        return -1;
    }

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

    //Allocation & indexing of vertex attribute memory for vertex shader
    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Texture index
    unsigned int texture;
    //Textures to generate
    glGenTextures(1, &texture);

    //Binding texture to type 2D texture
    glBindTexture(GL_TEXTURE_2D, texture);

    //Sets to use linear interpolation between adjacent mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //Sets to use linear interpolation upscaling (past largest mipmap texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Parameters that will be sent & set based on retrieved texture
    int width, height, colourChannels;
    //Retrieves texture data
    unsigned char* data = stbi_load("media/woodPlanks.jpg", &width, &height, &colourChannels, 0);

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

    //Render loop
    while (glfwWindowShouldClose(window) == false)
    {
        //Input
        ProcessUserInput(window); //Takes user input

        //Rendering
        glClearColor(0.25f, 0.0f, 1.0f, 1.0f); //Colour to display on cleared window
        glClear(GL_COLOR_BUFFER_BIT); //Clears the colour buffer

        //Drawing
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAOs[0]); //Bind buffer object to render; VAOs[0]
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

void ProcessUserInput(GLFWwindow* WindowIn)
{
    //Closes window on 'exit' key press
    if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(WindowIn, true);
    }
}