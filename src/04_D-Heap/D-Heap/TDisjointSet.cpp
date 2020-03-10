#include "TDisjointSet.h"

TDisjointSet::TDisjointSet(int _size)
{
    int size = _size;
    keys = new int[size];
    for (int i = 0; i < size; i++)
        keys[i] = -1;
}

TDisjointSet::TDisjointSet(int _size, int* _keys)
{
    int size = _size;
    keys = new int[size];
    for (int i = 0; i < size; i++)
        keys[i] = _keys[i];
}

TDisjointSet::~TDisjointSet()
{
    delete[] keys;
}

void TDisjointSet::makeSet(int x)
{
    keys[x] = x;
}

void TDisjointSet::unite(int r, int s)
{
    for (int i = 0; i < size; i++)
        if (keys[i] == s)
            keys[i] = r;
}

int TDisjointSet::find(int x)
{
    return keys[x];
}