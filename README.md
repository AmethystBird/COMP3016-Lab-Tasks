# Lab 1 - C++ Fundamentals
## Introduction
In this module, we will be using the OpenGL (Open Graphics Library) programming interface with the C++ language. For this reason, this lab will give an introduction to C++ with assumed understanding of other general purpose object oriented programming languages, such as C# & Java.

## Setup
All labs will utilise Visual Studio 2019 or 2022 with Windows 10 or 11. Run Visual Studio and click 'Create a new project' & create a project of type 'Console App' with the tags C++, Windows & Console. If this does not appear, then run the Visual Studio Installer. Find the relevant Visual Studio installation, select 'Modify' & install the 'Desktop development with C++' package. Now proceed to run Visual Studio to create the relevant project.

## Text Streaming
### std::cout
To print text to a console, the ```cout``` object can be used. The example project you created in [Setup](#setup) should already demonstrate this as such:

```c++
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
```

## Namespaces
You have may noticed that ```cout``` is prefixed & as such ```std::cout``` is written instead. If you try to remove the prefix, the code will not compile. This is because by default, the namespace ```std``` must be specified as a prefix to ```cout``` in order to allow for C++ to disambiguify what ```cout``` is referring to.

The reason that namespaces exist is in order to allow for multiple objects & functions to be given the same name without naming collisions occuring. Otherwise if multiple objects or functions were given the same name, the C++ compiler would not be able to differentiate them and the code would fail to compile.

For example, if one created two namespaces that both contained identically named but different functions, this code would compile:

```c++
int main()
{
    namespace1::Hello();
    namespace2::Hello();
}
```

However, if one particular namespace is being used more frequently than another, the namespace can be effectively hidden if one declares its use on the cpp file. While the use of the namespace prefix may still be used for the given namespace, it no longer has to be:

```c++
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!\n";
}
```