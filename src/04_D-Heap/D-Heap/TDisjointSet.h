#ifndef __TDISJOINTSET__H__
#define __TDISJOINTSET__H__

class TDisjointSet
{
    int size;
    int* keys;

public:
    explicit TDisjointSet(int _size);
    TDisjointSet(int _size, int* _keys);
    ~TDisjointSet();

    void makeSet(int x);
    void unite(int r, int s);
    int find(int x);
};

#endif // !__TDISJOINTSET__H__