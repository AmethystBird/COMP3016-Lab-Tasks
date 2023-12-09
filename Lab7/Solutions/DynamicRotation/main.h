#pragma once

#include <GLFW/glfw3.h>

//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Processes user input on a particular window
void ProcessUserInput(GLFWwindow* WindowIn);

GLuint program;