#include <iostream>
#include <cstdio>
#include "TList.h"


using namespace std;

int main()
{
    cout << "\t--List Test--" << endl;

    TList<int, int> L1;
    int a = 2;
    int* pa = &a;
    L1.InsertToStart(2, pa);
    L1.InsertToEnd(3, pa);

    TList<int, int>L2(L1);

    cout << "\n  List 1: " << endl;
    cout << L1;
    cout << "  List 2: " << endl;
    cout << L2;
    
    L1.InsertAfter(3, 4, pa);
    cout << "  Insert 4 after key 3 in L1: " << endl;
    cout << L1 << endl;
    try
    {
        cout << "  Insert 4 after key 25 in L1: " << endl;
        L1.InsertAfter(25, 4, pa);
        cout << L1;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    };

    L2.InsertBefore(2, 1, pa);
    cout << "  Insert 1 before key 2 in L2: " << endl;
    cout << L2;

    L2.InsertBefore(3, 10, pa);
    cout << "  Insert 10 before key 3 in L2: " << endl;
    cout << L2;

    L2.InsertToStart(7, pa);
    cout << "  Insert 7 to start in L2: " << endl;
    cout << L2;

    L2.InsertToEnd(9, pa);
    cout << "  Insert 9 to end in L2: " << endl;
    cout << L2;

    L2.InsertToEnd(11, pa);
    cout << "  Insert 11 to end in L2: " << endl;
    cout << L2;
    
    try 
    {
        L2.Remove(10);
        cout << "  Delete the elemtnt with key 10 in L2: " << endl;
        cout << L2;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    };
    getchar();
}