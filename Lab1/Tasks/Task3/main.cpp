#include "main.h"

#include <iostream>

Dragon* Dragon1;
Dragon* Dragon2;

int main()
{
    cout << "Input name for dragon 1:" << "\n";
    string name;
    cin >> name;
    Dragon1 = Dragon(name);
    cout << "Input health for dragon 1:" << "\n";
    int health;
    cin >> health;
    Dragon1.health = &health;
    Dragon1.DisplayAttributes();
    delete Dragon1;

    cout << "Input name for dragon 2:" << "\n";
    name;
    cin >> name;
    Dragon2 = Dragon(name);
    cout << "Input health for dragon 2:" << "\n";
    health;
    cin >> health;
    Dragon2.health = &health;
    Dragon2.DisplayAttributes();
    CompareDragons(Dragon1, Dragon2);
    delete Dragon2;
}

Dragon::Dragon(string* nameIn)
{
    name = &nameIn;
}

void Dragon::DisplayAttributes()
{
    cout << "Name: " << &name << "\n" << "Health: " << &health << "\n";
}

void CompareDragons(Dragon Dragon1In, Dragon Dragon2In)
{
    if (Dragon1In.health > Dragon2In.health)
    {
        cout << Dragon1In.name << "'s health is higher than " << Dragon2In.name << "'s.\n";
    }
    else
    {
        cout << Dragon2In.name << "'s health is higher than " << Dragon1In.name << "'s.\n";
    }
}
