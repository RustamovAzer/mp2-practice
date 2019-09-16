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
    friend ostream& operator<<(ostream&, const TVector&);
    friend istream& operator>>(istream&, TVector&);
};

template<class ValType>
TVector<ValType>::TVector(int size, int startIndfex) :size(size), startIndex(startIndex)
{
}

template<class ValType>
TVector<ValType>::TVector(const TVector<ValType>& _v) : size(_v.size), startIndex(startIndex)
{
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
    size = _v.size;
    startIndex = _v.startIndex;
    memccpy(elems, _v.elems);
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

ostream & operator<<(ostream & oustr, const TVector<class ValType>& _v)
{
    if (_v.size == 0)return oustr;
    for (size_t i = 0; i < _v.size; i++)
    {
        oustr << _v.elems[i];
    }
}


istream & operator>>(istream & instr, TVector<class ValType>& _v)
{
    if (_v.size == 0)return instr;
    for (size_t i = 0; i < _v.size; i++)
    {
        instr >> _v.elems[i];
    }
}

#endif