#version 460
//Colour value to send to next stage
out vec4 FragColor;
//Colour value from last stage
in vec3 fragColour;

void main()
{
    //RGBA values
    FragColor = vec4(fragColour, 1.0f);
}