#ifndef _TNODE_H_
#define _TNODE_H_
#include <iostream>
using namespace std;

template <typename TKey, typename TData>
struct TNode
{
    TKey key;
    TData* pData;
    TNode* pNext;

    TNode();
    TNode(TKey _key, TData* _data, TNode* _pNext = nullptr);
    TNode(const TNode<TKey, TData>*& _tnode);
    ~TNode();
    template<class TKey, class TData>
    friend ostream& operator<<(ostream& os, TNode<TKey, TData>& tmp);
};

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode()
{
    pData = new TData;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data, TNode* _pNext)
{
    key = _key;
    pData = new TData;
    pData = _data;
    pNext = _pNext;
    pData = nullptr;
    pNext = nullptr;
}


template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>*& _tnode)
{
    key = _tnode->key;
    pData = new TData;
    pData = _tnode->pData;
    pNext = _tnode->pNext;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
    if (pData)
        delete pData;
};



template<class TKey, class TData>
ostream & operator<<(ostream & os, TNode<TKey, TData>& tmp)
{
    if (tmp.pData != nullptr)
        os << "  " << tmp.key << " ";
    return os;
}

#endif