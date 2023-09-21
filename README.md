# Lab 1 - C++ Fundamentals
## Introduction
In this module, we will be using the OpenGL (Open Graphics Library) programming interface with the C++ language. For this reason, this lab will give an introduction to C++ with assumed understanding of other general purpose object oriented programming languages, such as C# & Java.

## Setup
All labs will utilise Visual Studio 2019 or 2022 with Windows 10 or 11. Run Visual Studio and click 'Create a new project' & create a project of type 'Console App' with the tags C++, Windows & Console. If this does not appear, then run the Visual Studio Installer. Find the relevant Visual Studio installation, select 'Modify' & install the 'Desktop development with C++' package. Now proceed to run Visual Studio to create the relevant project.

## Input and Output
### Output
To print text to a console, the ```cout``` object can be used. The example project you created in [Setup](#setup) should already demonstrate this as such:

```c++
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
```

### Input
To allow the user to input text to a console, the ```cin``` object can be used. Using ```cin``` will halt the program from running until a user gives input to the console and presses enter.

```c++
int main()
{
    std::cout << "Provide a number!\n";

    int number;
    std::cin >> number;
    std::cout << "Your number: " << number << "\n";
}
```

## Namespaces
### Overview
You have may noticed that both ```cout``` & ```cin``` are prefixed & as such ```std::cout``` & ```std::cin``` are written instead. This is because by default, both ```cout``` & ```cin``` are members of the ```std``` namespace. If the namespace is not specified as a prefix, the C++ compiler will not know what ```cout``` & ```cin``` refer to and the code will not compile.

Namespaces are groups of code, known as declarative regions. Their purpose is to isolate identifiers away from regions of code not under the same namespace. Examples of identifiers could be names for objects, functions & object variables. For example, this allows for a function outside of a namespace to be given the same name as an entirely separate function within another namespace:

```c++
//This will not run in your project, as neither of these namespaces have been declared.
int main()
{
    namespace1::Hello();
    namespace2::Hello();
}
```
### Default
Without namespaces, this would not be possible due to the C++ compiler being unable to disambiguify which name refers to what. The code would fail to compile as a result.

However, for the case where a particular namespace is being used more frequently than another within a cpp file, the namespace can be effectively hidden if one declares it as the default namespace for that cpp file. While the use of the namespace prefix may still be used for the given namespace, it no longer has to be used. Of course, this can only be done with one namespace per file, otherwise this would defeat the purpose of them as naming collisions could occur.

```c++
#include <iostream>

using namespace std; //The 'std' namespace will now be assumed

int main()
{
    cout << "Provide a number!\n";

    int number;
    cin >> number;
    cout << "Your number: " << number << "\n";
}
```
## Memory
### References
All data is stored in memory as a combination of a value & an address. The purpose of the address is to know the location of its associated value in memory. Therefore, whenever a variable is read or written to, the variable's address is accessed first to direct the program to the value.

In C++, when you copy a variable, you have the option to either copy it entirely (copy by value / deep copy) or only copy its address (copy by reference / shallow copy). Since the reference points to the same value as the preceding variable, the same result will be acquired. In order to hold a reference, the use of the ampersand ```&``` as a suffix to the variable type is used.

```c++
int main()
{
    int originalNumber = 64;
    int& referenceToNumber = originalNumber; //The '&' is used to declare a reference
    int copyOfNumber = originalNumber;
    cout << "Copy by Reference: " << referenceToNumber << "\n";
    cout << "Copy by Value: " << copyOfNumber << "\n";
}
```

One benefit of copying by reference is that it is faster than copying by value, as only the address must be copied as opposed to the entire variable. However, copying by reference is not always applicable. If the value that an address points to is modified, all references will point to the modified one. This is because there is only one value to point to. Try executing the following code to compare the difference between what ```referenceToNumber``` & ```copyOfNumber``` print.

```c++
int main()
{
    int originalNumber = 64;
    int& referenceToNumber = originalNumber;
    int copyOfNumber = originalNumber;

    originalNumber = 128;

    cout << "Copy by Reference: " << referenceToNumber << "\n";
    cout << "Copy by Value: " << copyOfNumber << "\n";
}
```

When ```originalNumber``` is modified, ```referenceToNumber``` mirrors this change. However, ```copyOfNumber``` does not. This is because the former points to the original value, whereas the latter points to a new, copied value.

When declaring a function, any parameters must also specify whether to copy by reference or value. For example, the code below achieves the same result as in the previous example, however ```originalNumber``` is now passed through a function. As one might expect, passing by reference through a function is faster than passing by value.

```c++
int main()
{
    originalNumber = 64; //Assigned as an object variable for purpose of demonstration
    Hello(originalNumber, originalNumber);
}

void Hello(int& number0In, int number1In)
{
    originalNumber = 128;
    cout << "Copy by Reference: " << number0In << "\n";
    cout << "Copy by Value: " << number1In << "\n";
}
```

### Pointers