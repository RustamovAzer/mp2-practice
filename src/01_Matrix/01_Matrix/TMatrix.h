#ifndef _TMATRIX_H
#define _TMATRIX_H

#include <iostream>
#include "TVector.h"

template<typename ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    explicit TMatrix(int _size = 10);
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


    friend ostream& operator<<(ostream& outputStream, const TMatrix<ValType>& matrix)
    {
        if (matrix.size == 0)
            return outputStream;
        for (size_t i = 0; i < matrix.size - 1; i++)
            outputStream << matrix.elems[i] << '\n';
        return outputStream << matrix.elems[matrix.size - 1];
    }
    friend istream& operator >> (istream& inputStream, TMatrix<ValType>& matrix)
    {
        if (matrix.size == 0)
            return inputStream;
        for (size_t i = 0; i < matrix.size; i++)
            inputStream >> matrix.elems[i];
        return inputStream;
    }
};

template<typename ValType>
TMatrix<ValType>::TMatrix(int _size) : TVector<TVector<ValType> >(_size)
{
    for (int i = 0; i < _size; i++)
        this->elems[i] = TVector<ValType>(_size - i, i);
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& temp)
{
   this->size = temp.size;
   this->elems = new TVector<ValType>[temp.size];
   for (int i = 0; i < temp.size; i++)
       this->elems[i] = temp.elems[i];
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& temp) : TVector<TVector<ValType> >(temp.GetSize())
{
    for (int i = 0; i <this->size; i++)
    {
        this->elems[i] = TVector<ValType>(this->size - i, i);
        for (int j = i; j <this->size; j++)
            this->elems[i][j] = temp[i][j];
    }
}

template<typename ValType>
TMatrix<ValType>::~TMatrix() {}

template<typename ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& temp) const
{
    if (this->size != temp.size)
        return false;
    for (int i = 0; i < temp.size; i++)
    {
        if (this->elems[i] != temp.elems[i])
        {
            return false;
        }
    }
    return true;
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
    if (this->size != temp.size)
    {
        this->size = temp.size;
        delete[] this->elems;
        this->elems = new TVector<ValType>[temp.size];
    }
    for (int i = 0; i < temp.size; i++)
        this->elems[i] = temp.elems[i];
    return *this;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(ValType temp)
{
    TMatrix<ValType> rez(*this);
    for (int i = 0; i < rez.size; i++)
        rez.elems[i] = this->elems[i] + temp;
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(ValType temp)
{
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i < this->size; i++)
        rez.elems[i] = rez.elems[i] - temp;
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType temp)
{
    TMatrix<ValType> rez(*this);
    for (size_t i = 0; i <this->size; i++)
        rez.elems[i] = rez.elems[i] * temp;
    return rez;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& temp)
{
    if (this->size != temp.size)
        throw (char*)"Размерности не совпадают";
    TMatrix<ValType> res(this->size);
    for (int i = 0; i < res.size; i++)
        res.elems[i] = this->elems[i] + temp.elems[i];
    return res;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& temp)
{
    if (this->size != temp.size)
        throw (char*)"Размерности не совпадают";
    TMatrix<ValType> res(this->size);
    for (int i = 0; i < res.size; i++)
        res.elems[i] = this->elems[i] - temp.elems[i];
    return res;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& temp)
{
    if (this->size != temp.size)
        throw (char*)"Размерности не совпадают";
    TMatrix<ValType> rez(*this);
    for (int i = 0; i < rez.size; i++)
    {
        int cols = 1;
        int si = temp.elems[i].GetStartIndex();
        for (int j = si; j < rez.size; j++)
        {
            rez.elems[i][j] = ValType(0);
            for (int k = 0; k < cols; k++)
                rez.elems[i][j] = rez.elems[i][j] + this->elems[i][k + i] * temp.elems[k + i][j];
            cols++;
        }
    }
    return rez;
}

template<typename ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& temp)
{
    int _size = temp.GetSize();
    if (this->size != _size)
        throw (char*)"Размерности не совпадают";
    TVector<ValType> rez(_size);
    for (int i = 0; i < _size; i++)
    {
        rez[i] = ValType(0);
        int si = this->elems[i].GetStartIndex();
        for (int j = si; j < _size; j++)
            rez[i] = rez[i] + this->elems[i][j] * temp[j];
    }
    return rez;
}

template<typename ValType>
ValType TMatrix<ValType>::Determinant()
{
    ValType res;
    res = ValType(1);
    for (size_t i = 0; i <this->size; i++)
        res = res * this->elems[i][i];
    return res;
}


#endif