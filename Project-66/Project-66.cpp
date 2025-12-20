#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand(time(nullptr));

    std::cout << "Hello World!\n";
}