#ifndef _TMONOM_H_
#define _TMONOM_H_
#include <iostream>
#include <string>
using namespace std;


template <typename TKey, typename TData>
class TMonom
{
    TKey key;
    TData data;
    TMonom* pNext;

    TMonom();
    TMonom(TKey _key, TData _data, TMonom* _pNext = nullptr);
    TMonom(const TMonom<TKey, TData>*& _tnode);
    ~TMonom();
    template<class TKey, class TData>
    friend ostream& operator<<(ostream& os, TMonom<TKey, TData>& tmp);
};

template <typename TKey, typename TData>
TMonom<TKey, TData>::TMonom()
{
    pNext = nullptr;
}

template <typename TKey, typename TData>
TMonom<TKey, TData>::TMonom(TKey _key, TData _data, TMonom* _pNext)
{
    key = _key;
    data = _data;
    pNext = _pNext;
    data = nullptr;
    pNext = nullptr;
}


template <typename TKey, typename TData>
TMonom<TKey, TData>::TMonom(const TMonom<TKey, TData>*& _tnode)
{
    key = _tnode->key;
    data = new TData;
    data = _tnode->data;
    pNext = _tnode->pNext;
}

template<typename TKey, typename TData>
TMonom<TKey, TData>::~TMonom()
{
}



template<class TKey, class TData>
ostream & operator<<(ostream & os, TMonom<TKey, TData>& tmp)
{
    os << "  " << tmp.key << " ";
    return os;
}

/////////////////////////////////////////////////


using namespace std;

const int NPOS = -1;

template <>
class TMonom<int, double>
{
public:
    int key;
    double data;
    TMonom* pNext;

    TMonom();
    TMonom(int _key, double _data, TMonom* _pNext = nullptr);
    TMonom(const TMonom<int, double>*& _tnode);
    TMonom(const string _expression);

    ~TMonom();
    template<>
    friend ostream& operator<<(ostream& os, TMonom<int, double>& tmp);
};


TMonom<int, double>::TMonom(int _key, double _data, TMonom* _pNext)
{
    key = _key;
    data = _data;
    pNext = _pNext;
    pNext = nullptr;
}



TMonom<int, double>::TMonom<int, double>(const TMonom<int, double>*& _tnode)
{
    key = _tnode->key;
    data = _tnode->data;
    pNext = _tnode->pNext;
}


TMonom<int, double>::TMonom<int, double>(string _expression)
{
    key = 0;
    double neg = 1;
    if (_expression[0] = '-')
        neg = -1;
    int start_of_coef = _expression.find_first_of("1234567890");
    int end_of_coef = _expression.find_first_not_of("1234567890.");
        if (end_of_coef == NPOS)
            throw exception("Invalid monom");
    string coefstr = _expression.substr(start_of_coef, end_of_coef - start_of_coef);
    data = neg * stod(coefstr);

    int operand = _expression.find_first_of("xyz");
    if (_expression[operand] == 'x')
    {
        if (_expression[operand + 1] == '^')
        {
            char a = _expression[operand + 2];
            int ia = a - '0';
            key += 100 * ia;
            operand = operand + 2;
        }
        key += 100;
        operand = operand + 1;
    }
    if (_expression[operand] == 'y')
    {
        if (_expression[operand + 1] == '^')
        {
            char a = _expression[operand + 2];
            int ia = a - '0';
            key += 100 * ia;
            operand = operand + 2;
        }
        key += 10;
        operand = operand + 1;
    }
    if (_expression[operand] == 'z')
    {
        if (_expression[operand + 1] == '^')
        {
            char a = _expression[operand + 2];
            int ia = a - '0';
            key += 100 * ia;
            operand = operand + 2;
        }
        key += 1;
        operand = operand + 1;
    }
}


template<>
ostream & operator<<(ostream & os, TMonom<int, double>& tmp)
{
    if (tmp.data != 0)
        os << "  " << tmp.data << "x^"<<tmp.key / 100 <<"y^"<<(tmp.key % 100) / 10 <<"z^"<<tmp.key % 10<<" ";
    return os;
}

#endif