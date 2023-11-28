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