#include "main.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    Dragon Dragon1("TrueDragon");
    Dragon* Dragon2 = new Dragon("Wyvern");
    delete Dragon2; //If not deleted, will continue to exist after going out of scope
}

Dragon::Dragon(string typeIn)
{
    type = typeIn;
}