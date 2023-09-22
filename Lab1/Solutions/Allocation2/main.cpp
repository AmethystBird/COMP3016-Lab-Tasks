#include "main.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    Dragon Dragon1("TrueDragon");
    cout << Dragon1.type << "\n";
    Dragon1.Roar();

    Dragon* Dragon2 = new Dragon("Wyvern");
    cout << Dragon2->type << "\n";
    Dragon2->Roar();
    delete Dragon2;
}

Dragon::Dragon(string typeIn)
{
    type = typeIn;
}

void Dragon::Roar()
{
    cout << "Roar!" << "\n";
}
