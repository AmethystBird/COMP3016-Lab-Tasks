#include "main.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    Dragon* Dragon2 = new Dragon("Wyvern");
    Dragon2->Die(); //Deallocates itself within function, leaving empty pointer
    cout << Dragon2->type << "\n"; //This will not print the Dragon2 type
}

Dragon::Dragon(string typeIn)
{
    type = typeIn;
}

void Dragon::Die()
{
    cout << type << " died!" << "\n";
    delete this; //deallocation of itself (Dragon2)
}
