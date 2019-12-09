#ifndef _TMONOM_H_
#define _TMONOM_H_
#include <iostream>
using namespace std;

template <typename TKey, typename TData>
struct TMonom
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
    pNext = nullptr;
}


template <typename TKey, typename TData>
TMonom<TKey, TData>::TMonom(const TMonom<TKey, TData>*& _tnode)
{
    key = _tnode->key;
    data = _tnode->data;
    pNext = _tnode->pNext;
}

template<typename TKey, typename TData>
TMonom<TKey, TData>::~TMonom()
{
};



template<class TKey, class TData>
ostream & operator<<(ostream & os, TMonom<TKey, TData>& tmp)
{
    if (tmp.data != 0)
        os << "  " << tmp.data << "x^"<<tmp.key / 100 <<"y^"<<(tmp.key % 100) / 10 <<"z^"<<tmp.key%10<<" ";
    return os;
}

#endif