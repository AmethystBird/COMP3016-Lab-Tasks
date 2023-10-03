#include "main.h"

#include <iostream>

int main()
{
	Colour* AmbiguousColour = new Colour("Ambiguous");
	Red* TypeofColour = new Red("Red");

	Colour* TechnicallyRed = (Colour*)TypeofColour; //Pointer to 'Red' object is of type 'Colour*'

	delete AmbiguousColour;
	delete TypeofColour;
}

Colour::Colour(string typeIn)
{
	type = typeIn;
}
