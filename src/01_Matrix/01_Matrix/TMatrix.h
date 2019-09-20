#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include "TVector.h"

using namespace std;

template<class ValType>
class TMatrix: public TVector<TVector<ValType> >
{
public:
    TMatrix(int size = 10);
    TMatrix(const TMatrix&);
    TMatrix(const TVector<TVector<ValType> >&);
    ~TMatrix();
    //TMatrix& operator=(const TMatrix&);
    //bool operator==(const TMatrix&)const;
    //bool operator!=(const TMatrix&)const;
    //TMatrix operator+(ValType);
    //TMatrix operator-(ValType);
    //TMatrix operator*(ValType);
    //TMatrix operator+(const TMatrix&);
    //TMatrix operator-(const TMatrix&);
    TMatrix operator*(const TMatrix&);
    TVector operator*(const TVector&);
    ValType Det();
    friend ostream& operator<<(ostream&, const TMatrix&);
    friend istream& operator>>(istream&, TMatrix&);

private:

};

template<class ValType>
TMatrix<ValType>::TMatrix(int size)
{
    elems = new TVector<TVector<ValType> >[size];
    /*
    for (size_t i = 0; i < size; i++)
    {
        this->elems[i] = new TVector<ValType>;
    }
    */
}

template<class ValType>
TMatrix<ValType>::TMatrix(const TMatrix & _v)
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
    for (size_t i = 0; i < size; i++)
    {
        elems[i] = _v.elems[i];
    }
}

template<class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& _v)
{
    if (size != _v.size)
    {
        size = _v.size;
    }
    if (startIndex != _v.startIndex)
    {
        startIndex = _v.startIndex;
    }
    for (size_t i = 0; i < size; i++)
    {
        elems[i] = _v.elems[i];
    }
}

template<class ValType>
TMatrix<ValType>::~TMatrix()
{
    if (size>0)
    {
        for (size_t i = 0; i < size; i++) delete elems[i];
    }
    delete[] elems;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix & _v)
{
    if (size == _v.size) throw "Unequal sizes";
    TMatrix<ValType>(size) res;
    /*
    for (size_t k = 0; i < size; i++)
    {
        for (size_t i = 0; i < size; i++)
        {
           elems[k][i] = 0;
           for (size_t j = 0; j < size; j++)
           {
               res.elems[k][i] += elems[k][j] * _v[j][i];
           }
        }
    }
       
    */
    return //
}

/*template<class ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector & _v)
{
    return TVectorr();
}*/






#endif