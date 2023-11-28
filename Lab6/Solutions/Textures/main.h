#pragma once

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>

//#include "glslprogram.h"

//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Processes user input on a particular window
void ProcessUserInput(GLFWwindow* WindowIn);

GLuint program;
//GLSLProgram program;