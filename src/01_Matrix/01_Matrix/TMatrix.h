#ifndef _TMATRIX_H
#define _TMATRIX_H

#include <iostream>
#include "TVector.h"

template<typename ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
    explicit TMatrix(size_t _size = 10);
    TMatrix(const TMatrix&);
    TMatrix(const TVector<TVector<ValType> >&);
    ~TMatrix();
    bool operator==(const TMatrix&) const;
    bool operator!=(const TMatrix&) const;
    TMatrix& operator=(const TMatrix&);
    TMatrix operator+(ValType);
    TMatrix operator-(ValType);
    TMatrix operator*(ValType);
    TMatrix operator+(const TMatrix&);
    TMatrix operator-(const TMatrix&);
    TMatrix operator*(const TMatrix&);
    TVector<ValType> operator*(const TVector<ValType>&);

    ValType Determinant();


    friend ostream& operator<<(ostream& out, const TMatrix& _v)
    {
        for (size_t i = 0; i < _v.size; i++)
        {
            out << _v.elems[i] << "\n";
        }
        return out;
    }
    friend istream& operator >> (istream& in, TMatrix& temp)
    {
        for (size_t i = 0; i < temp.size; i++)
            in >> temp.elems[i];
        return in;
    }
};

template<typename ValType>
TMatrix<ValType>::TMatrix(size_t _size) : TVector<TVector<ValType> >(_size)
{
    for (int i = 0; i < _size; i++)
        elems[i] = TVector<ValType>(_size - i, i);
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& temp)
{
    size = temp.size;
    elems = new TVector<ValType>[temp.size];
    for (size_t i = 0; i < temp.size; i++)
        elems[i] = temp.elems[i];
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& temp) : TVector<TVector<ValType> >(temp.GetSize())
{
    for (size_t i = 0; i < size; i++)
    {
        elems[i] = TVector<ValType>(size - i, i);
        for (size_t j = i; j < size; j++)
            elems[i][j] = temp[i][j];
    }
}

template<typename ValType>
TMatrix<ValType>::~TMatrix() {}

template<typename ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& temp) const
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    for (size_t i = 0; i < temp.size; i++)
    {
        if (elems[i] != temp.elems[i])
        {
            return 0;
        }
    }
    return 1;
}

template<typename ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& temp) const
{
    return (!(*this == temp));
}

template<typename ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& temp)
{
    if (this == &temp)
        return *this;
    if (size != temp.size)
    {
        size = temp.size;
        delete[] elems;
        elems = new TVector<ValType>[temp.size];
    }
    for (int i = 0; i < temp.size; i++)
        elems[i] = temp.elems[i];
    return *this;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(ValType temp)
{
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < rez.size; i++)
        rez.elems[i] = elems[i] + temp;
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(ValType temp)
{
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = rez.elems[i] - temp;
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType temp)
{
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = rez.elems[i] * temp;
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& temp)
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < rez.size; i++)
        rez.elems[i] = elems[i] + temp.elems[i];
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& temp)
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < rez.size; i++)
        rez.elems[i] = elems[i] - temp.elems[i];
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& temp)
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < rez.size; i++)
    {
        size_t cols = 1;
        size_t si = temp.elems[i].GetStartIndex();
        for (size_t j = si; j < rez.size; j++)
        {
            rez.elems[i][j] = ValType(0);
            for (size_t k = 0; k < cols; k++)
                rez.elems[i][j] = rez.elems[i][j] + elems[i][k + i] * temp.elems[k + i][j];
            cols++;
        }
    }
    return rez;
}

template<typename ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& temp)
{
    size_t _size = temp.GetSize();
    if (size != _size)
        throw "Размерности не совпадают";
    TVector<ValType> rez(_size);
    for (size_t i = 0; i < _size; i++)
    {
        rez[i] = ValType(0);
        size_t si = elems[i].GetStartIndex();
        for (size_t j = si; j < _size; j++)
            rez[i] = rez[i] + elems[i][j] * temp[j];
    }
    return rez;
}

template<typename ValType>
ValType TMatrix<ValType>::Determinant()
{
    ValType res;
    res = ValType(1);
    for (size_t i = 0; i < size; i++)
        res = res * elems[i][i];
    return res;
}


#endif