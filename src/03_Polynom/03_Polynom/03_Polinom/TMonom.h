#ifndef _TMONOM_H_
#define _TMONOM_H_

#include <iostream>
#include "TNode.h"

class TMonom : public TNode<unsigned, double>
{
public:
    TMonom(unsigned key_, const double* pData_);
    TMonom(unsigned key_, const double& data);
    TMonom(const TMonom& temp);
    TMonom(const TNode<unsigned, double>& temp);
    ~TMonom();

    TMonom operator*(const TMonom& temp);

    friend std::ostream& operator<<(std::ostream& out, const TMonom& monom);

    TMonom operator-() const;
};

TMonom::TMonom(unsigned key_, const double* pData_) : TNode<unsigned, double>(key_, pData_)
{
    if (key > 999 || *pData == 0) throw exception("Incorrect degree");
}

TMonom::TMonom(unsigned key_, const double& data) : TNode<unsigned, double>(key_, data)
{
    if (key > 999 || *pData == 0) throw exception("Incorrect degree");
}

TMonom::TMonom(const TMonom& temp) : TNode<unsigned, double>(temp)
{
    if (key > 999 || *pData == 0) throw exception("Incorrect degree");
}

TMonom::TMonom(const TNode<unsigned, double>& temp) : TNode<unsigned, double>(temp)
{
    if (key > 999 || *pData == 0) throw exception("Incorrect degree");
}

TMonom::~TMonom()
{

}

TMonom TMonom::operator*(const TMonom& temp)
{
    if ((key / 100 + temp.key / 100) >= 10) 
        throw exception("Incorrect degree");
    if ((key % 100 / 10 + temp.key % 100 / 10) >= 10) 
        throw exception("Incorrect degree");
    if ((key % 10 + temp.key % 10) >= 10) 
        throw exception("Incorrect degree");
    TMonom out(key + temp.key, *pData * *(temp.pData));
    return out;
}


std::ostream& operator<<(std::ostream& out, const TMonom& monom) 
{
    if (*(monom.pData) > 0)
        out << "+";
    else
        out << "-";
    if ((*(monom.pData) != 1 && *(monom.pData) != -1) || monom.key == 0)
        out << abs(*(monom.pData));
    if (monom.key / 100 == 1)
        out << "x";
    if ((monom.key / 100 != 0)&&(monom.key / 100 != 1))
        out << "x^" << (monom.key / 100);
    if (monom.key % 100 / 10 == 1)
        out << "y";
    if ((monom.key % 100 / 10 != 0) && (monom.key % 100 / 10 != 1))
        out << "y^" << (monom.key % 100 / 10);
    if (monom.key % 10 == 1)
        out << "z";
    if ((monom.key % 10 != 0) && (monom.key % 10 != 1))
        out << "z^" << (monom.key % 10);
    return out;
}

TMonom TMonom::operator-() const
{
    TMonom out(key, -*(pData));
    return out;
}
#endif