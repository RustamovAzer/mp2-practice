#include <iostream>
#include "TPolynom.h"


int main()
{
    TPolynom first, second;
    try
    {
        std::cout << "Enter the first polynom:" << std::endl;
        std::cin >> first;
        std::cout << "Enter the second polynom:" << std::endl;
        std::cin >> second;
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }

    std::cout << "Sum:" << std::endl;
    std::cout << first + second << std::endl;
    std::cout << "Substraction" << std::endl;
    std::cout << first - second << std::endl;
    std::cout << "Multiplication" << std::endl;



    try
    {
        std::cout << first * second << std::endl;
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
    system("pause");
}