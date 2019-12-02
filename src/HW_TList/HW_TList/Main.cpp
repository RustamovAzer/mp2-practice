#include <iostream>
#include "TList.h"

using namespace std;

void main()
{
    cout << "\t--List Test--" << endl;

    TList<int, int> L1;
    int a[1] = { 2 };
    L1.InsertBegin(2, a);
    L1.Push(3, a);

    TList<int, int>L2(L1);

    cout << "\n  List 1: ";
    cout << L1;
    cout << "  List 2: ";
    cout << L2;

    TNode<int, int> *f1, *f2;
    cout << endl << "  Find the element with key 2: ";
    f1 = L2.Search(2);
    if (f1 != nullptr)
    {
        cout << f1 << endl;
    }
    else
    {
        cout << "cannot find the element";
    }
    cout << endl << "  Find the element with key 25: ";
        f2 = L2.Search(25);
    if (f2 != nullptr)
    {
        cout << f2 << endl;
    }
    else
    {
        cout << "cannot find the element" << endl;
    }


    L1.InsertAfter(3, 4, a);
    cout << "  Insert 4 after key 3: ";
    cout << L1;
    try
    {
        cout << "  Insert 4 after key 25: ";
        L1.InsertAfter(25, 4, a);
        cout << L1;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    };

    L2.InsertBefore(2, 1, a);
    cout << "  Insert 1 before key 2: ";
    cout << L2;

    L2.InsertBefore(3, 10, a);
    cout << "  Insert 10 before key 3: ";
    cout << L2;

    L2.InsertBegin(7, a);
    cout << "  Insert 7 to start: ";
    cout << L2;

    L2.Push(9, a);
    cout << "  Insert 9 to end: ";
    cout << L2;

    L2.Push(11, a);
    cout << "  Insert 11 to end: ";
    cout << L2;

    L2.Remove(10);
    cout << "  Delete the elemtnt with key 10: ";
    cout << L2;

    cin.get();
}