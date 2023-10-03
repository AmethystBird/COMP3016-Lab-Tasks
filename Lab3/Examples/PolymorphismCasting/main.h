#pragma once

#include <string>

using namespace std;

class Colour {
public:
	Colour(string typeIn);
	string type;
};

class Red : public Colour {
public:
	Red(string typeIn) : Colour(typeIn) {}
};