#pragma once

#include <string>

using namespace std;

class Dragon
{
public:
    Dragon(string& nameIn);
    string name;
    int health;

    void DisplayAttributes();
};

void CompareDragons(Dragon* Dragon1In, Dragon* Dragon2In);