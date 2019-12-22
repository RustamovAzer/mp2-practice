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

    friend std::ostream& operator<<(std::ostream& out, const TPolynom& polynom);
    friend std::istream& operator >> (std::istream& in, TPolynom& polynom);

    friend TPolynom operator-(TPolynom temp);
};

TPolynom::TPolynom()
{
    list = new TList<unsigned, double>;
}

TPolynom::TPolynom(const TList<unsigned, double>& list_)
{
    list = new TList<unsigned, double>;
    TNode<unsigned, double>* iter = list_.pFirst;
    while (iter != nullptr)
    {
        *this += (TMonom)*iter;
        iter = iter->pNext;
    }
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
    if (this == &temp) return *this;
    delete list;
    list = new TList<unsigned, double>(*(temp.list));
    return *this;
}

TPolynom TPolynom::operator+(const TPolynom& temp)
{
    TPolynom out;
    TNode<unsigned, double>* first = list->pFirst;
    TNode<unsigned, double>* second = temp.list->pFirst;
    while (first != nullptr || second != nullptr)
    {
        if (first == nullptr)
        {
            out.list->InsertToEnd(second->key, second->pData); //
            second = second->pNext;
        }
        else if (second == nullptr)
        {
            out.list->InsertToEnd(first->key, first->pData); //
            first = first->pNext;
        }
        else if (first->key > second->key)
        {
            out.list->InsertToEnd(first->key, first->pData); //
            first = first->pNext;
        }
        else if (first->key < second->key)
        {
            out.list->InsertToEnd(second->key, second->pData); //
            second = second->pNext;
        }
        else
        {
            if (*(first->pData) != -*(second->pData))
            {
                out.list->InsertToEnd(first->key, *(first->pData) + *(second->pData)); //
            }
            first = first->pNext;
            second = second->pNext;
        }
    }
    /*out += *this;
    out += temp;*/
    return out;
}

TPolynom& TPolynom::operator+=(const TPolynom& temp)
{
    TNode<unsigned, double>* first = list->pFirst;
    TNode<unsigned, double>* second = temp.list->pFirst;
    if (first == nullptr)
    {
        delete list;
        list = new TList<unsigned, double>(*(temp.list));
        return *this;
    }
    if (second == nullptr)
    {
        return *this;
    }
    if (first->key < second->key) 
    {
        list->InsertToStart(second->key, second->pData);
        first = list->pFirst;
        second = second->pNext;
    }
    while (second != nullptr)
    {
        if (first->pNext == nullptr)
        {
            first->pNext = new TMonom(*(second));
            first = first->pNext;
            second = second->pNext;
        }
        else if (first->pNext->key > second->key)
        {
            first = first->pNext;
        }
        else if (first->pNext->key < second->key)
        {
            TNode<unsigned, double>* temp = new TMonom(*(second));
            temp->pNext = first->pNext;
            first->pNext = temp;
            first = first->pNext;
            second = second->pNext;
        }
        else
        {
            if (*(first->pNext->pData) != -*(second->pData))
                *(first->pNext->pData) += *(second->pData);
            else
                list->Remove(first->pNext->key);
            second = second->pNext;
        }
    }
    return *this;
}

TPolynom TPolynom::operator+(const TMonom& node)
{
    TPolynom out;
    TNode<unsigned, double>* first = list->pFirst;
    bool isInserted = false;
    while (first != nullptr || !isInserted)
    {
        if (first == nullptr)
        {
            out.list->InsertToStart(node.key, node.pData);
            isInserted = true;
        }
        else if (first->key > node.key)
        {
            out.list->InsertToStart(first->key, first->pData);
            first = first->pNext;
        }
        else if (!isInserted && first->key < node.key)
        {
            out.list->InsertToStart(node.key, node.pData);
            isInserted = true;
        }
        else if (!isInserted)
        {
            if (*(first->pData) != -*(node.pData))
            {
                out.list->InsertToStart(first->key, *(first->pData) + *(node.pData));
            }
            first = first->pNext;
            isInserted = true;
        }
        else
        {
            out.list->InsertToStart(first->key, first->pData);
            first = first->pNext;
        }
    }
    return out;
}

TPolynom& TPolynom::operator+=(const TMonom& node)
{
    TNode<unsigned, double>* first = list->pFirst;
    if (first == nullptr || node.key > first->key)
    {
        list->InsertToStart(node.key, node.pData);
        return *this;
    }
    while ((first->pNext != nullptr) && (first->pNext->key > node.key))
        first = first->pNext;
    if ((first->pNext != nullptr) && (first->pNext->key == node.key))
    {
        if (*(first->pNext->pData) != -*(node.pData))
            *(first->pNext->pData) += *(node.pData);
        else
            list->Remove(first->pNext->key);
        return *this;
    }
    TNode<unsigned, double>* temp = new TNode<unsigned, double>(node);
    temp->pNext = first->pNext;
    first->pNext = temp;
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
    TPolynom out;
    TNode<unsigned, double>* second = temp.list->pFirst;
    if (second == nullptr)
    {
        return out;
    }
    while (second != nullptr)
    {
        out += *this * *second;
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

TPolynom operator-(TPolynom temp)
{
    TPolynom out(temp);
    TNode<unsigned, double>* iter = out.list->pFirst;
    while (iter != nullptr)
    {
        *(iter->pData) *= -1;
        iter = iter->pNext;
    }
    return out;
}
#endif