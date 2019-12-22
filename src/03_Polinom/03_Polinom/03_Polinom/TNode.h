#ifndef _TNODE_H_
#define _TNODE_H_
#include <iostream>
using namespace std;

template<typename TKey, typename TData>
struct TNode
{
    TKey key;
    TData* pData;
    TNode* pNext;

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
    key = NULL;
    pData = new TData;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey key_, const TData* pData_)
{
    key = key_;
    pData = new TData;
    *pData = *pData_;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey key_, const TData& data_)
{
    key = key_;
    pData = new TData;
    *pData = data_;
    pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& temp)
{
    key = temp.key;
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
    key = temp.key;
    *pData = *(temp.pData);
    return *this;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& out, const TNode<TKey, TData>& node)
{
    out << "Key: " << node.key << " Data: " << *(node.pData);
    return out;
};
#endif