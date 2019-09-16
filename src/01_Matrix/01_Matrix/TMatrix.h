#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include "TVector.h"

using namespace std;

template<class ValType>
class TMatrix: public TVector
{
public:
    TMatrix(int size = 10);
    TMatrix(const TMatrix&);
    TMatrix(const TVector<TVector<TVector> >&);
    ~TMatrix();
    TMatrix& operator=(const TMatrix&);
    bool operator==(const TMatrix&)const;
    bool operator!=(const TMatrix&)const;
    TMatrix operator+(ValType);
    TMatrix operator-(ValType);
    TMatrix operator*(ValType);
    TMatrix operator+(const TMatrix&);
    TMatrix operator-(const TMatrix&);
    TMatrix operator*(const TMatrix&);
    TMatrix operator*(const TVector&);
    ValType Det();
    friend ostream& operator<<(ostream&, const TMatrix&);
    friend istream& operator>>(istream&, TMatrix&);

private:

};

template<class ValType>
TMatrix<ValType>::TMatrix(int size): size(size)
{

}

#endif