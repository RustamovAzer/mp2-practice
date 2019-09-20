#ifndef _TVECTOR_H_/
#define _TVECTOR_H_
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

template<class ValType>
class TVector
{
protected:
    
    int size;
    ValType* elems;
    int startIndex;
    
public:

    TVector(int size = 10, int startIndfex = 0);
    TVector(const TVector<ValType>& _v);
    ~TVector();
    bool operator==(const TVector& _v) const;
    bool operator!=(const TVector& _v) const;
    TVector& operator=(const TVector& _v);
    TVector operator+(ValType _x);
    TVector operator-(ValType _x);
    TVector operator*(ValType _x);
    TVector operator+(const TVector& _v);
    TVector operator-(const TVector& _v);
    ValType operator*(const TVector&);
    ValType& operator[](int index);
    ValType Length()const;
    int GetSize()const;
    int GetStartIndex()const;
    friend ostream & operator<<(ostream & out, const TVector<class ValType> & _v)
    {
        if (_v.size == 0)return out;
        for (size_t i = 0; i < _v.size; i++)
        {
            out << _v.elems[i];
        }
    }
    friend istream & operator>>(istream & in, TVector<class ValType>& _v)
    {
        if (_v.size == 0)return in;
        for (size_t i = 0; i < _v.size; i++)
        {
            in >> _v.elems[i];
        }
    }

};

template<class ValType>
TVector<ValType>::TVector(int _size, int _startIndfex)
{
    size = _size;
    startIndex = _startIndfex;
    elems = new ValType[size];
}

template<class ValType>
TVector<ValType>::TVector(const TVector<ValType>& _v)
{
    size = _v.size;
    startIndex = _v.startIndfex;
    elems = new ValType[size];
    memcpy(elems, _v.elems, size * sizeof(ValType));
}

template<class ValType>
TVector<ValType>::~TVector()
{
    if (size>0)
    {
        delete elems[];
    }
}

template<typename ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType>& _v)
{
    if (elems == _v.elems) throw "Self-assignment";
    if (size != _v.size)
    {
        size = _v.size;
    }
    if (startIndex != _v.startIndex)
    {
        startIndex = _v.startIndex;
    }
    memcpy(elems, _v.elems, size * sizeof(ValType));
    return *this;
}



template<typename ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& _v)const
{
    if (size == _v.size)
    {
        if(!memcmp(elems,_v.elems, size * sizeof(ValType))
            return true;
    }
    return false;
}



template<typename ValType>
bool TVector<ValType>::operator!=(const TVector & _v)const
{

    if (size != _v.size)
    {
        if(memcmp(elems,_v.elems, size * sizeof(ValType))
        return true;
    }
    return false;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(ValType _x)
{
    TVector<ValType> tmp = *this;
    for (size_t i = 0; i < size; i++)
    {
        tmp.elems[i] += x;
    }
    return tmp;
}
template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(ValType _x)
{
    TVector<ValType> tmp = *this;
    for (size_t i = 0; i < size; i++)
    {
        tmp.elems[i] -= x;
    }
    return tmp;
}
template<typename ValType>
TVector<ValType> TVector<ValType>::operator*(ValType _x)
{
    TVector<ValType> tmp = *this;
    for (size_t i = 0; i < size; i++)
    {
        tmp.elems[i] *= x;
    }
    return tmp;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector &_v)
{
    TVector<ValType> tmp = *this;
    if (size == _v.size)
    {
        for (size_t i = 0; i < size; i++)
        {
            tmp.elems[i] += _v.elems;
        }
    }
    return tmp;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector &_v)
{
    TVector<ValType> tmp = *this;
    if (size == _v.size)
    {
        for (size_t i = 0; i < size; i++)
        {
            tmp.elems[i] -= _v.elems;
        }
    }
    return tmp;
}
template<typename ValType>
ValType TVector<ValType>::operator*(const TVector &_v)
{
    if (size == _v.size) throw "Unequal sizes";
    ValType res = elems[0]*_v.elems[0];
    if (size == _v.size)
    {
        for (size_t i = 1; i < size; i++)
        {
            res+= elems[i]*_v.elems;
        }
    }
    return res;
}

template<typename ValType>
ValType & TVector<ValType>::operator[](int index)
{
    if (index < 0) || (index >= size) throw "Incorrect index";
    return elems[index];
}

template<typename ValType>
ValType TVector<ValType>::Length() const
{
    ValType sqres = elems[0] * elems[0];
    for (size_t i = 1; i < size; i++)
    {
        sqres += elems[i] * elems[i];
    }
    ValType res = sqrt(sqres)
    return res;
}
template<class ValType>
int TVector<ValType>::GetSize() const
{
    return size;
}
template<class ValType>
int TVector<ValType>::GetStartIndex() const
{
    return startIndex;
}
#endif