#include "main.h"
#include "dragon.h"

int health;

int main()
{
    //Executing upon player
    health = 20;
    Hello();
    TakeDamage(3);
    Health();

    //Executing upon dragon
    health = 40;
    Hello();
    Roar();
    TakeDamage(4);
    Health();
}

void Hello()
{
    cout << "Hello dragon!" << "\n";
}

void Health()
{
    cout << "Player's health is: " << health << "\n";
}

void TakeDamage(int damage)
{
    health = health - damage;

    if (health < 0)
    {
        health = 0;
    }
}
