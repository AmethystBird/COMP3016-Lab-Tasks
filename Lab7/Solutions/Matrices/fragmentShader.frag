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