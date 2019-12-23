#ifndef _TNODE_H_
#define _TNODE_H_
#include <iostream>
using namespace std;

template<class TKey, class TData>
struct  TNode
{
    TKey Key;
    TData* pData;
    TNode<TKey, TData>* pNext;

    TNode();
    TNode(TKey key_, const TData* pData_);
    TNode(TKey key_, const TData& data);
    TNode(const TNode<TKey, TData>& temp);
    ~TNode();

    TNode<TKey, TData>& operator=(const TNode<TKey, TData>& temp);

    template <typename TKey, typename TData>
    friend std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node);
};

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode()
{
    Key = NULL;
    pData = new TData;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey key_, const TData* pData_)
{
    Key = key_;
    pData = new TData;
    *pData = *pData_;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey key_, const TData& data_)
{
    Key = key_;
    pData = new TData;
    *pData = data_;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& temp)
{
    Key = temp.Key;
    pData = new TData;
    *pData = *(temp.pData);
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
    delete pData;
}

template <typename TKey, typename TData>
TNode<TKey, TData>& TNode<TKey, TData>::operator=(const TNode<TKey, TData>& temp)
{
    if (this == &temp)
    {
        return *this;
    }
    Key = temp.Key;
    *pData = *(temp.pData);
    return *this;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node)
{
    out << "[ " << node.Key << " | " << *(node.pData)<< " ]";
    return out;
}
#endif