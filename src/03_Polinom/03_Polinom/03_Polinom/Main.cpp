#include <iostream>
#include <random>
#include <time.h>

#include "TPolynom.h"


int main()
{
    TPolynom first, second;
    srand((unsigned)time(0));
    std::cout << "Constructor from list test" << std::endl;
    TList<unsigned, double> list;
    for (int i = 0; i < 6; i++)
    {
        list.InsertToStart(rand() % 1000, 1 + rand() % 100);
    }
    std::cout << TPolynom(list) << std::endl;

    try
    {
        std::cout << "Enter first polynom:" << std::endl;
        std::cin >> first;
        std::cout << "Enter second polynom:" << std::endl;
        std::cin >> second;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    std::cout << "Sum:" << std::endl;
    std::cout << first + second << std::endl;;
    std::cout << "Substraction" << std::endl;
    std::cout << first - second << std::endl;;
    std::cout << "Multiplication" << std::endl;
    try
    {
        std::cout << first * second << std::endl;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    system("pause");
}