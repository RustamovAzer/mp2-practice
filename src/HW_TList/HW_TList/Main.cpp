#include <iostream>
#include "TList.h"

using namespace std;

void main()
{
    cout << "\t--List Test--" << endl;

    TList<int, int> L1;
    int a[1] = { 2 };
    L1.Push(a, 2);
    L1.Back(a, 3);

    TList<int, int>L2(L1);

    cout << "\n  List 1: ";
    L1.Print();
    cout << "  List 2: ";
    L2.Print();

    cout << endl << "  Find the element with key 2: " << L2.Search(2) << endl;

    L1.InsertAfter(3, a, 4);
    cout << "  Insert after key 3: ";
    L1.Print();

    L2.InsertBefore(2, a, 1);
    cout << "  Insert before key 2: ";
    L2.Print();

    L2.InsertBefore(3, a, 10);
    cout << "  Insert before key 3: ";
    L2.Print();

    L2.Remove(10);
    cout << "  Delete the elemtnt with key 10: ";
    L2.Print();
