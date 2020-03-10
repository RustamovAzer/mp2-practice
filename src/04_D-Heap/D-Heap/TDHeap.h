#ifndef __TDHEAP__H__
#define __TDHEAP__H__

template<typename T>
class TDHeap
{
public:
    int d;
    int maxSize;
    int size;
    T* keys;

public:
    TDHeap(int _d, int _maxSize);
    TDHeap(int _d, int _maxSize, int _size, T* _keys);
    ~TDHeap();

    void transpose(int a, int b);
    void siftUp(int _key);
    void siftDown(int _key);
    void removeMinKey();
    void heapify();
    T getRoot();

private:
    int minChild(int _key);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

template<typename T>
TDHeap<T>::TDHeap(int _d, int _maxSize)
{
    d = _d;
    maxSize = _maxSize;
    size = 0;
    keys = new T[maxSize];
}

template<typename T>
TDHeap<T>::TDHeap(int _d, int _maxSize, int _size, T* _keys)
{
    d = _d;
    maxSize = _maxSize;
    size = _size;
    keys = new T[maxSize];
    for (int i = 0; i < size; i++)
        keys[i] = _keys[i];
    heapify();
}

template<typename T>
TDHeap<T>::~TDHeap()
{
    delete[] keys;
    maxSize = 0;
    size = 0;
}

template<typename T>
void TDHeap<T>::transpose(int i, int j)
{
    T tmp = keys[i];
    keys[i] = keys[j];
    keys[j] = tmp;
}

template<typename T>
void TDHeap<T>::siftUp(int _key)
{
    while (_key > 0)
    {
        int parentKey = (_key - 1) / d;
        if (keys[parentKey] > keys[_key])
        {
            transpose(parentKey, _key);
            _key = parentKey;
        }
        else break;
    }
}

template<typename T>
void TDHeap<T>::siftDown(int _key)
{
    int minChildKey = minChild(_key);
    while ((minChildKey != -1) && (keys[minChildKey] < keys[_key]))
    {
        transpose(minChildKey, _key);
        _key = minChildKey;
        minChildKey = minChild(_key);
    }
}

template<typename T>
void TDHeap<T>::removeMinKey()
{
    transpose(0, size - 1);
    size--;
    siftDown(0);
}

template<typename T>
void TDHeap<T>::heapify()
{
    for (int i = size - 1; i >= 0; i--)
        siftDown(i);
}

template<typename T>
T TDHeap<T>::getRoot()
{
    return keys[0];
}

template<typename T>
int TDHeap<T>::minChild(int _key)
{
    if (_key * d + 1 >= size)
        return -1;

    int c1 = _key * d + 1;
    int c2 = (size - 1 < _key * d + d) ? (size - 1) : (_key * d + d);
    int minChildKey = c1;

    for (int i = c1 + 1; i <= c2; i++)
        if (keys[i] < keys[minChildKey])
            minChildKey = i;
    return minChildKey;
};

#endif // !__TDHEAP__H__