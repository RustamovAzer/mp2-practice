#include "../Algorithms/Algorithms.h"
#include "iostream"

int main()
{
    int maxSize = 10;
    int size = 10;
    int d = 2;
    int* keys = new int[maxSize];
    keys[0] = -1;
    keys[1] = 8;
    keys[2] = 0;
    keys[3] = -4;
    keys[4] = -2;
    keys[5] = 5;
    keys[6] = 4;
    keys[7] = 1;
    keys[8] = 2;
    keys[9] = 7;

    std::cout << "[ ";
    for (int i = 0; i < size; i++)
        std::cout << keys[i] << " ";
    std::cout << "]" << std::endl;

    HeapSort::heapSort(size, keys);

    std::cout << std::endl << "[ ";
    for (int i = 0; i < size; i++)
        std::cout << keys[i] << " ";
    std::cout << "]" << std::endl;

    std::cout << "//~~~~~~~~~~~~~~~~~~~~~~~~~~~//" << std::endl << std::endl;

    system("pause");
    return 0;
}