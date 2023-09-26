#pragma once

#include <string>

using namespace std;

class Orange {
public:
	Orange();
	int sweetness;
};

class Pomelo {
public:
	Pomelo();
	int bitterness;
};

class Grapefruit : Orange, Pomelo {
public:
	Grapefruit(string variationIn);
private:
	string variation;
};