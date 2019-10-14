#ifndef _TVECTOR_H
#define _TVECTOR_H

#include <iostream>
#include <iomanip>

using namespace std;

template<typename ValType>
class TVector
{
protected:
    int size, startIndex;
    ValType* elems;

public:
    explicit TVector(int _size = 2, int _startIndex = 0);
    TVector(const TVector&);
    ~TVector();

    bool operator==(const TVector&) const;
    bool operator!=(const TVector&) const;

    TVector& operator=(const TVector&);

    TVector operator+(ValType);
    TVector operator-(ValType);
    TVector operator*(ValType);

    TVector operator+(const TVector&);
    TVector operator-(const TVector&);

    ValType operator*(const TVector&);
    ValType Length() const;

    int GetSize() const;
    int GetStartIndex() const;

    TVector& Transpose();
    ValType& operator[](int);
    const ValType& operator[](int) const;
    


    friend ostream& operator<<(ostream& outputStream, const TVector& vector)
    {
        outputStream << "[ ";
        if (vector.size == 0)
            return outputStream << ']';
        for (size_t i = 0; i < vector.startIndex; i++)
            outputStream << setw(5) << setprecision(2) << right << ValType(0) << ' ';
        for (size_t i = 0; i < vector.size; i++)
            outputStream << setw(5) << setprecision(2) << right << vector.elems[i] << ' ';
        return outputStream << ']';
    }
    friend istream& operator >> (istream& inputStream, TVector& vector)
    {
        if (vector.size == 0)
            return inputStream;
        for (size_t i = 0; i < vector.size; i++)
            inputStream >> vector.elems[i];
        return inputStream;
    }
};

///////////////////////////////////////////////////////////////////////////////


template<typename ValType>
TVector<ValType>::TVector(int _size, int _startIndex)
{
    if (_size <= 0) throw std::exception("Нельзя создать вектор неположительной длины");
    size = _size;
    elems = new ValType[size];
    startIndex = _startIndex;
}

template<typename ValType>
TVector<ValType>::TVector(const TVector& temp)
{
    size = temp.size;
    elems = new ValType[size];
    for (size_t i = 0; i < size; i++) elems[i] = temp.elems[i];
    startIndex = temp.startIndex;
}

template<typename ValType>
TVector<ValType>::~TVector()
{
    delete[] elems;
}

template<typename ValType>
bool TVector<ValType>::operator==(const TVector& temp) const
{
    if ((size != temp.size)||(startIndex != temp.startIndex))
        return false;
    for (int i = 0; i < size; i++)
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
TVector<ValType> & TVector<ValType>::operator=(const TVector & temp)
{
    if (*this == temp)
        return *this;
    if (size != temp.size)
    {
        size = temp.size;
        delete[] elems;
        elems = new ValType[size];
    }
    startIndex = temp.startIndex;
    for (int i = 0; i < temp.size; i++)
        elems[i] = temp.elems[i];
    return *this;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(ValType temp)
{
    TVector<ValType> res(*this);
    for (int i = 0; i < size; i++)
        res.elems[i] = elems[i] + temp;
    return res;
}



template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(ValType temp)
{
    TVector<ValType> res(*this);
    for (int i = 0; i < size; i++)
        res.elems[i] = res.elems[i] - temp;
    return res;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator*(ValType temp)
{
    TVector<ValType> rez(*this);
    for (int i = 0; i < size; i++)
        rez.elems[i] = rez.elems[i] * temp;
    return rez;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& temp)
{
    if (size != temp.size)
        throw std::exception("Размерности не совпадают");
    TVector<ValType> res(this->size,this->startIndex);
    for (int i = 0; i < size; i++)
        res.elems[i] = this->elems[i] + temp.elems[i];
    return res;
}

template<typename ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& temp)
{
    if (size != temp.size)
        throw std::exception("Размерности не совпадают");///
    TVector<ValType> res(this->size, this->startIndex);
    for (int i = 0; i < size; i++)
        res.elems[i] = this->elems[i] - temp.elems[i];
    return res;
}

template<typename ValType>
ValType TVector<ValType>::operator*(const TVector& temp)
{
    if (size != temp.size)
        throw std::exception("Размерности не совпадают");
    ValType res = 0;
    for (int i = 0; i < size; i++)
        res += elems[i] * temp.elems[i];
    return res;
}

template<typename ValType>
ValType TVector<ValType>::Length() const
{
    return sqrt((*this) * (*this));
}

template<typename ValType>
int TVector<ValType>::GetSize() const
{
    return size;
}

template<typename ValType>
int TVector<ValType>::GetStartIndex() const
{
    return startIndex;
}

template<typename ValType>
ValType& TVector<ValType>::operator[](int index)
{
    if ((index - startIndex) >= size)
        throw std::exception("Выход за размерность вектора");
    return elems[index - startIndex];
}

template<typename ValType>
const ValType& TVector<ValType>::operator[](int index) const
{
    if ((index - startIndex) >= size)
        throw std::exception("Выход за размерность вектора");
    return elems[index - startIndex];
}



template<typename ValType>
TVector<ValType>& TVector<ValType>::Transpose()
{
    for (int i = 0; i < (size / 2); i++)
    {
        ValType tmp = elems[i];
        elems[i] = elems[size - 1 - i];
        elems[size - 1 - i] = tmp;
    }
    return *this;
}

#endif