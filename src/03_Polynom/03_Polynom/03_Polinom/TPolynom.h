#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_
#include <string>
#include <iostream>

#include "TList.h"
#include "TMonom.h"

class TPolynom
{
public:
    TList<unsigned, double>* list;

public:
    TPolynom();
    TPolynom(const TList<unsigned, double>& list_);
    TPolynom(const TPolynom& temp);
    ~TPolynom();

    TPolynom& operator=(const TPolynom& temp);

    TPolynom operator+(const TPolynom& temp);
    TPolynom operator-(const TPolynom& temp);
    TPolynom operator*(const TPolynom& temp);

    TPolynom& operator+=(const TPolynom& temp);
    TPolynom& operator-=(const TPolynom& temp);

    TPolynom operator+(const TMonom& node);
    TPolynom operator-(const TMonom& node);
    TPolynom operator*(const TMonom& node);

    TPolynom& operator+=(const TMonom& node);
    TPolynom& operator-=(const TMonom& node);
    TPolynom& operator*=(const TMonom& node);

    bool operator==(const TPolynom& temp) const;

    friend std::ostream& operator<<(std::ostream& out, const TPolynom& polynom);
    friend std::istream& operator >> (std::istream& in, TPolynom& polynom);

    TPolynom operator-() const;
};

TPolynom::TPolynom()
{
    list = new TList<unsigned, double>;
}

TPolynom::TPolynom(const TList<unsigned, double>& list_)
{
    list = new TList<unsigned, double>(list_);
}

TPolynom::TPolynom(const TPolynom& temp)
{
    list = new TList<unsigned, double>(*(temp.list));
}

TPolynom::~TPolynom()
{
    delete list;
}

TPolynom& TPolynom::operator=(const TPolynom& temp)
{
    if (*this == temp) return *this;
    delete list;
    list = new TList<unsigned, double>(*(temp.list));
    return *this;
}

TPolynom TPolynom::operator+(const TPolynom& temp)
{
    TPolynom out;
    TNode<unsigned, double>* first = list->pFirst;
    TNode<unsigned, double>* second = temp.list->pFirst;
    while ((first != nullptr )&&( second != nullptr))
    {
        
        if (first->key > second->key)
        {
            out.list->InsertToEnd(first->key, first->pData); 
            first = first->pNext;
        }
        else if (first->key < second->key)
        {
            out.list->InsertToEnd(second->key, second->pData); 
            second = second->pNext;
        }
        else
        {
            if (*(first->pData) != -*(second->pData))
            {
                out.list->InsertToEnd(first->key, *(first->pData) + *(second->pData)); 
            }
            first = first->pNext;
            second = second->pNext;
        }

        if (first == nullptr)
        {
            while (second != nullptr)
            {
                out.list->InsertToEnd(second->key, second->pData);
                second = second->pNext;
            }
            
        }
        else if (second == nullptr)
        {
            while (first != nullptr)
            {
                out.list->InsertToEnd(first->key, first->pData);
                first = first->pNext;
            }
            
        }
    }

    return out;
}

TPolynom& TPolynom::operator+=(const TPolynom& temp)
{
    TPolynom copy = *this;
    *this = copy + temp;
    return *this;
}

TPolynom TPolynom::operator+(const TMonom& node)
{
    TPolynom out;

    TNode<unsigned, double>* first = list->pFirst;
    bool isInserted = false;
    while ((first != nullptr) && (!isInserted))
    {
        
        if (first->key > node.key)
        {
            out.list->InsertToEnd(first->key, first->pData);
            first = first->pNext;
        }
        else if (first->key < node.key)
        {
            out.list->InsertToEnd(node.key, node.pData);
            isInserted = true;
        }
        
    }

    if (first == nullptr)
    {
        out.list->InsertToEnd(node.key, node.pData);
    }

    if (isInserted)
    {
        while (first != nullptr)
        {
            out.list->InsertToEnd(first->key, first->pData);
            first = first->pNext;
        }

    }

    return out;
}

TPolynom& TPolynom::operator+=(const TMonom& node)
{

    TPolynom copy = *this;
    *this = copy + node;
    return *this;
}

TPolynom TPolynom::operator-(const TPolynom& temp)
{
    return *this + (-temp);
}

TPolynom& TPolynom::operator-=(const TPolynom& temp)
{
    return *this += (-temp);
}

TPolynom TPolynom::operator-(const TMonom& node)
{
    return *this + (-node);
}

TPolynom& TPolynom::operator-=(const TMonom& node)
{
    return *this += (-node);
}

TPolynom TPolynom::operator*(const TPolynom& temp)
{
    TPolynom out, tmpres;
    TNode<unsigned, double>* second = temp.list->pFirst;
    if (second == nullptr)
    {
        return out;
    }

    tmpres = *this * *second;
    out = tmpres;
    second = second->pNext;

    while (second != nullptr)
    {
        tmpres = *this * *second;
        out += tmpres;
        second = second->pNext;
    }

    

    return out;
}

TPolynom TPolynom::operator*(const TMonom& node)
{
    TPolynom out(*this);
    TNode<unsigned, double>* first = out.list->pFirst;
    while (first != nullptr)
    {
        *first = (TMonom)(*first) * node;
        first = first->pNext;

    }
    return out;
}

TPolynom& TPolynom::operator*=(const TMonom& node)
{
    TNode<unsigned, double>* first = list->pFirst;
    while (first != nullptr)
    {
        *first = (TMonom)*first * node;
        first = first->pNext;
    }
    return *this;
}

bool TPolynom::operator==(const TPolynom & temp) const
{
    bool out = true;
    TNode<unsigned, double>* first = list->pFirst;
    TNode<unsigned, double>* second = temp.list->pFirst;
    while ((first != nullptr)&&(second != nullptr))
    {
        if ((first->key != second->key) || (*(first->pData) != *(second->pData)))
            out = false;
        first = first->pNext;
        second = second->pNext;
    }
    if ((second != nullptr)||(first != nullptr))
        out = false;

    return out;
}

std::ostream& operator<<(std::ostream& out, const TPolynom& polynom)
{
    TNode<unsigned, double>* iter = polynom.list->pFirst;
    if (iter == nullptr)
    {
        out << "0";
        return out;
    }
    while (iter != nullptr)
    {
        out << (TMonom)*iter << ' ';
        iter = iter->pNext;
    }
    return out;
}

std::istream& operator >> (std::istream& in, TPolynom& polynom)
{
    delete polynom.list;
    polynom.list = new TList<unsigned, double>;
    std::string line, buffer;
    std::getline(in, line);
    int coef = 0, mul = 1, mode = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ' && !buffer.empty())
        {
            if (mul == 0) throw exception("Incorrect input 1");
            if (stof(buffer) != 0)
            {
                polynom += TMonom(coef, mul * std::stof(buffer));
            }
            buffer.clear();
            mul = 0;
            coef = 0;
            mode = 0;
        }
        else if (line[i] == '+')
        {
            if (mode == 1) throw exception("Incorrect input 2");
            mul = 1;
        }
        else if (line[i] == '-')
        {
            if (mode == 1) throw exception("Incorrect input 3");
            mul = -1;
        }
        else if ((line[i] > 47 && line[i] < 58) || line[i] == '.')
        {
            buffer.push_back(line[i]);
            if (mode == 1) throw exception("Incorrect input 4");
        }
        else if (line[i] == 'x')
        {
            mode = 1;
            if (buffer.empty()) buffer = "1";
            if (line[i + 1] == '^')
            {
                if (line[i + 2] < 48 || line[i + 2] > 57) 
                    throw exception("Incorrect input 5");
                if ((line[i + 2] - 48) + (coef / 100) > 9) 
                    throw exception("Incorrect degree");
                coef += 100 * (line[i + 2] - 48);
                i = i + 2;
                continue;
            }
            else
            {
                if (coef / 100 == 9) throw exception("Incorrect degree");
                coef += 100;
                continue;
            }
        }
        else if (line[i] == 'y')
        {
            mode = 1;
            if (buffer.empty()) buffer = "1";
            if (line[i + 1] == '^')
            {
                if (line[i + 2] < 48 || line[i + 2] > 57) throw exception("Incorrect input");
                if ((line[i + 2] - 48) + ((coef % 100) / 10) > 9) throw exception("Incorrect degree");
                coef += 10 * (line[i + 2] - 48);
                i = i + 2;
                continue;
            }
            else
            {
                if ((coef % 100) / 10 == 9) throw exception("Incorrect degree");
                coef += 10;
                continue;
            }
        }
        else if (line[i] == 'z')
        {
            mode = 1;
            if (buffer.empty()) buffer = "1";
            if (line[i + 1] == '^')
            {
                if (line[i + 2] < 48 || line[i + 2] > 57) throw exception("Incorrect input");
                if ((line[i + 2] - 48) + (coef % 10) > 9) throw exception("Incorrect degree");
                coef += (line[i + 2] - 48);
                i = i + 2;
                continue;
            }
            else
            {
                if (coef % 10 == 9) throw exception("Incorrect degree");
                coef += 1;
                continue;
            }
        }
        else if (line[i] != ' ')
        {
            throw exception("Incorrect input");
        }
    }
    if (!buffer.empty())
    {
        polynom += TMonom(coef, mul * std::stof(buffer));
        buffer.clear();
        coef = 0;
    }
    return in;
}

TPolynom TPolynom::operator-() const
{
    TPolynom out(*this);
    TNode<unsigned, double>* iter = out.list->pFirst;
    while (iter != nullptr)
    {
        *(iter->pData) *= -1;
        iter = iter->pNext;
    }
    return out;
}
#endif