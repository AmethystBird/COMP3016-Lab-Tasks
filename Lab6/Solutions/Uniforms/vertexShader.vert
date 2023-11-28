#version 460
//Triangle position with values retrieved from main.cpp
layout (location = 0) in vec3 position;

void main()
{
    //Triangle vertices sent through gl_Position to next stage
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}