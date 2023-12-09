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