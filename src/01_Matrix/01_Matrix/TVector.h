#ifndef _TVECTOR_H
#define _TVECTOR_H

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

template<typename ValType>
class TVector
{
protected:
    size_t size, startIndex;
    ValType* elems;

public:
    explicit TVector(size_t _size = 2, size_t _startIndex = 0);
    TVector(const TVector&);
    ~TVector();

    bool operator==(const TVector&) const;
    bool operator!=(const TVector&) const;

    TVector operator+(ValType);
    TVector operator-(ValType);
    TVector operator*(ValType);

    TVector operator+(const TVector&);
    TVector operator-(const TVector&);

    ValType operator*(const TVector&);
    ValType Length() const;

    size_t GetSize() const;
    size_t GetStartIndex() const;
    void SetStartIndex(size_t);

    TVector& Transpose();
    ValType& GetValue(size_t);
    const ValType& GetValue(size_t) const;
    ValType& operator[](size_t);
    const ValType& operator[](size_t) const;
    TVector& operator=(const TVector&);

    void GenerateVector();

    friend ostream& operator<<(ostream& out, const TVector& _v)
    {
        if (_v.size == 0)
            return out;
        out << "| ";
        for (size_t i = 0; i < _v.startIndex; i++)
            out << setw(6) << setprecision(4) << right << ValType(0) << "|";
        for (size_t i = 0; i < _v.size; i++)
            out << setw(6) << setprecision(4) << right << _v.elems[i] << "|";
        return out;
    }
    friend istream& operator >> (istream& in, TVector& temp)
    {
        if (temp.size == 0)
            return in;
        for (size_t i = 0; i < temp.size; i++)
        {
            cout << "Введите " << i + 1 << " элемент: ";
            in >> temp.elems[i];
        }
        return in;
    }
};

///////////////////////////////////////////////////////////////////////////////


template<typename ValType>
TVector<ValType>::TVector(size_t _size, size_t _startIndex)
{
    srand((unsigned)time(0));
    size = _size;
    elems = new ValType[size];
    startIndex = _startIndex;
}

template<typename ValType>
TVector<ValType>::TVector(const TVector& temp)
{
    size = temp.size;
    elems = new ValType[size];
    memcpy(elems, temp.elems, sizeof(ValType) * size);
    startIndex = temp.startIndex;
}

template<typename ValType>
TVector<ValType>::~TVector()
{
    if (size > 0)
        delete[] elems;
}

template<typename ValType>
bool TVector<ValType>::operator==(const TVector& temp) const
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    for (size_t i = 0; i < size; i++)
    {
        if (elems[i] != temp.elems[i])
        {
            return false;
        }
    }
    return true;
}

template<typename ValType>
bool TVector<ValType>::operator!=(const TVector& temp) const
{
    return !(*this == temp);
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(ValType temp)
{
    TVector<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = elems[i] + temp;
    return rez;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(ValType temp)
{
    TVector<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = rez.elems[i] - temp;
    return rez;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator*(ValType temp)
{
    TVector<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = rez.elems[i] * temp;
    return rez;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& temp)
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    TVector<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = temp.elems[i] + rez.elems[i];
    return rez;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& temp)
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    TVector<ValType> rez(*this);
    for (size_t i = 0; i < size; i++)
        rez.elems[i] = rez.elems[i] - temp.elems[i];
    return rez;
}

template<typename ValType>
ValType TVector<ValType>::operator*(const TVector& temp)
{
    if (size != temp.size)
        throw "Размерности не совпадают";
    ValType rez = 0;
    for (size_t i = 0; i < size; i++)
        rez = rez + elems[i] * temp.elems[i];
    return rez;
}

template<typename ValType>
ValType TVector<ValType>::Length() const
{
    ValType rez = 0;
    for (size_t i = 0; i < size; i++)
        rez += elems[i] * elems[i];
    return sqrt(rez);
}

template<typename ValType>
size_t TVector<ValType>::GetSize() const
{
    return size;
}

template<typename ValType>
size_t TVector<ValType>::GetStartIndex() const
{
    return startIndex;
}

template<typename ValType>
ValType& TVector<ValType>::operator[](size_t index)
{
    if ((index - startIndex) >= size)
        throw "Выход за размерность вектора";
    return elems[index - startIndex];
}

template<typename ValType>
const ValType& TVector<ValType>::operator[](size_t index) const
{
    if ((index - startIndex) >= size)
        throw "Выход за размерность вектора";
    return elems[index - startIndex];
}

template<typename ValType>
ValType& TVector<ValType>::GetValue(size_t index)
{
    if (index >= size)
        throw "Выход за размерность вектора";
    return elems[index];
}

template<typename ValType>
const ValType& TVector<ValType>::GetValue(size_t index) const
{
    if (index >= size)
        throw "Выход за размерность вектора";
    return elems[index];
}

template<typename ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& temp)
{
    if (this != &temp)
    {
        if (size != temp.size)
        {
            size = temp.size;
            delete elems;
            elems = new ValType[size];
        }
        startIndex = temp.startIndex;
        memcpy(elems, temp.elems, sizeof(ValType) * size);
    }
    return *this;
}

template<typename ValType>
void TVector<ValType>::GenerateVector()
{
    ValType lb = 1, rb = 100;
    for (size_t i = 0; i < size; i++)
        elems[i] = lb + ((ValType)rand() / RAND_MAX) * (rb - lb);
}

template<typename ValType>
void TVector<ValType>::SetStartIndex(size_t si)
{
    startIndex = si;
}

template<typename ValType>
TVector<ValType>& TVector<ValType>::Transpose()
{
    for (size_t i = 0; i < (size / 2); i++)
    {
        ValType tmp = elems[i];
        elems[i] = elems[size - 1 - i];
        elems[size - 1 - i] = tmp;
    }
    return *this;
}

;
#endif