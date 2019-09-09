
#include <iostream>

using namespace std;

template<typename ValType>
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
    TVector<ValType> operator=(const TVector<ValType>&)
    bool operator==(const TVector<ValType>&)const;
    bool operator!=(const TVector<ValType>&)const;
    TVector<ValType> operator+(ValType);
    TVector<ValType> operator-(ValType);
    TVector<ValType> operator*(ValType);
    TVector<ValType> operator+(const TVector&);
    TVector<ValType> operator-(const TVector&);
    ValType operator*(const TVector&);
    ValType& operator[](int index);
    ValType Length()const;
    int Size()const;
    int StartIndex()const;
    friend ostream& operator<<(ostream&, const TVector&);
    friend istream& operator>>(istream&, TVector&);
};


template<typename ValType>
TVector<ValType> TVector<ValType>::operator=(const TVector<ValType>& _v)
{
    if (elems == _v.elems) throw (string)"Self-assignment";
    size = _v.size;
    startIndex = _v.startIndex;
    memccpy(elems, _v.elems);
    return *this;
}



template<typename ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& _v)
{
    if (size == _v.size)
    {
        if(memcmp(elems,_v.elems)
            return true;
    }
    return false;
}

template<typename ValType>
bool TVector<ValType>::operator!=(const TVector & _v) const
{

    if (size != _v.size)
    {
        if(!memcmp(elems,_v.elems)
        return true;
    }
    return false;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(ValType x)
{
    TVector<ValType> tmp = *this;
    for (size_t i = 0; i < size; i++)
    {
        tmp.elems[i] += x;
    }
    return tmp;
}
template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(ValType x)
{
    TVector<ValType> tmp = *this;
    for (size_t i = 0; i < size; i++)
    {
        tmp.elems[i] -= x;
    }
    return tmp;
}
template<typename ValType>
TVector<ValType> TVector<ValType>::operator*(ValType x)
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
    if (size < index) return elems[index];
}

template<typename ValType>
ValType TVector<ValType>::Length() const
{
    //ValType res = 
    return ValType();
}

