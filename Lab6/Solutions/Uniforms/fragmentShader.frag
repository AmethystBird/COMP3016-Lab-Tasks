#version 460
//Colour value to send to next stage
out vec4 FragColor;
//Colour value
uniform vec4 colourIn;

void main()
{
    //RGBA values
    FragColor = colourIn;
}