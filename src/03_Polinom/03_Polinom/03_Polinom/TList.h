#ifndef  _TLIST_H_
#define _TLIST_H_
#include <iostream>
#include "TNode.h"
using namespace std;

template <typename TKey, typename TData>
class TList
{
protected:
    TNode<TKey, TData>* pFirst;
    TNode<TKey, TData>* pPrevious;
    TNode<TKey, TData>* pNext;
    TNode<TKey, TData>* pCurrent;

public:
    TList();
    TList(const TList<TKey, TData>& temp);
    TList(TNode<TKey, TData>* node_);
    ~TList();

    void InsertToStart(TKey key_, const TData* pData_);
    void InsertToEnd(TKey key_, const TData* pData_);
    void InsertBefore(TKey key_where, TKey key_, const TData* pData_);
    void InsertAfter(TKey key_where, TKey key_, const TData* pData_);

    void InsertToStart(TKey key_, const TData& data_);
    void InsertToEnd(TKey key_, const TData& data_);
    void InsertBefore(TKey key_where, TKey key_, const TData& data_);
    void InsertAfter(TKey key_where, TKey key_, const TData& data_);

    void Remove(TKey key_);

    void Reset();
    bool IsEnded() const;
    bool IsEmpty() const;
    void Next();

    template <typename TKey, typename TData>
    friend ostream& operator<<(ostream& out, const TList<TKey, TData>& list);
    friend ostream& operator<<(ostream& out, const TList<unsigned, double>& list);

    friend class TPolynom;
    friend ostream& operator<<(ostream& out, const TPolynom& polynom);
};

template <typename TKey, typename TData>
TList<TKey, TData>::TList()
{
    pFirst = nullptr;
    pPrevious = nullptr;
    pNext = nullptr;
    pCurrent = nullptr;
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& temp)
{
    if (temp.pFirst == nullptr)
    {
        pFirst = nullptr;
        pPrevious = nullptr;
        pNext = nullptr;
        pCurrent = nullptr;
        return;
    }
    pFirst = new TNode<TKey, TData>(*(temp.pFirst));
    TNode<TKey, TData> *node_ = pFirst, *node_temp = temp.pFirst;
    while (node_temp->pNext != nullptr)
    {
        node_->pNext = new TNode<TKey, TData>(*(node_temp->pNext));
        node_ = node_->pNext;
        node_temp = node_temp->pNext;
    }
    pPrevious = nullptr;
    if (pFirst != nullptr) pNext = pFirst->pNext;
    pCurrent = pFirst;
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(TNode<TKey, TData >* node_)
{
    if (node_ == nullptr)
    {
        pFirst = nullptr;
        pPrevious = nullptr;
        pNext = nullptr;
        pCurrent = nullptr;
        return;
    }
    pFirst = new TNode<TKey, TData>(*node_);
    TNode<TKey, TData> *node = pFirst, *node_temp = node_;
    while (node_temp->pNext != nullptr)
    {
        node->pNext = new TNode<TKey, TData>(*(node_temp->pNext));
        node = node->pNext;
        node_temp = node_temp->pNext;
    }
    pPrevious = nullptr;
    if (pFirst != nullptr) pNext = pFirst->pNext;
    pCurrent = pFirst;
}

template <typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
    TNode<TKey, TData> *del = pFirst, *next;
    while (del != nullptr)
    {
        next = del->pNext;
        delete del;
        del = next;

    }
}


template <typename TKey, typename TData>
void TList<TKey, TData>::InsertToStart(TKey key_, const TData* pData_)
{
    if (pFirst == nullptr)
    {
        pFirst = new TNode<TKey, TData>(key_, pData_);
        pCurrent = pFirst;
        return;
    }
    TNode<TKey, TData>* temp = new TNode<TKey, TData>(key_, pData_);
    temp->pNext = pFirst;
    if (pCurrent == pFirst) pPrevious = temp;
    pFirst = temp;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertToEnd(TKey key_, const TData* pData_)
{
    if (pFirst == nullptr)
    {
        pFirst = new TNode<TKey, TData>(key_, pData_);
        pCurrent = pFirst;
        return;
    }
    TNode<TKey, TData>* temp = new TNode<TKey, TData>(key_, pData_);
    TNode<TKey, TData>* node = pFirst;
    while (node->pNext != nullptr)
    {
        node = node->pNext;
    }
    node->pNext = temp;
    if (pCurrent == node) pNext = temp;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey key_where, TKey key_, const TData* pData_)
{
    if (pFirst == nullptr) return;
    if (pFirst->key == key_where)
    {
        InsertToStart(key_, pData_);
        return;
    }
    TNode<TKey, TData>* prev_node = pFirst;
    while ((prev_node->pNext != nullptr) && (prev_node->pNext->key != key_where))
    {
        prev_node = prev_node->pNext;
    }
    if (prev_node->pNext == nullptr) 
        throw exception("Key not found");
    TNode<TKey, TData>* next_node = prev_node->pNext;
    TNode<TKey, TData>* temp = new TNode<TKey, TData>(key_, pData_);
    prev_node->pNext = temp;
    temp->pNext = next_node;
    if (pCurrent == prev_node) pNext = temp;
    if (pCurrent == next_node) pPrevious = temp;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey key_where, TKey key_, const TData* pData_)
{
    if (pFirst == nullptr) return;
    TNode<TKey, TData>* prev_node = pFirst;
    while ((prev_node != nullptr) && (prev_node->key != key_where))
    {
        prev_node = prev_node->pNext;
    }
    if (prev_node == nullptr) 
        throw exception("Key not found");
    TNode<TKey, TData>* next_node = prev_node->pNext;
    TNode<TKey, TData>* temp = new TNode<TKey, TData>(key_, pData_);
    prev_node->pNext = temp;
    temp->pNext = next_node;
    if (pCurrent == prev_node) pNext = temp;
    if (pCurrent == next_node) pPrevious = temp;

}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertToStart(TKey key_, const TData& data_)
{
    InsertToStart(key_, &data_);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertToEnd(TKey key_, const TData& data_)
{
    InsertToEnd(key_, &data_);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey key_b, TKey key_, const TData& data_)
{
    InsertBefore(key_b, key_, &data_);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey key_a, TKey key_, const TData& data_)
{
    InsertAfter(key_a, key_, &data_);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Remove(TKey key_)
{
    if (pFirst == nullptr) return;
    if (pFirst->key == key_)
    {
        TNode<TKey, TData>* next_node = pFirst->pNext;
        if (pCurrent == pFirst) pCurrent = nullptr;
        if (pPrevious == pFirst) pPrevious = nullptr;
        if (pNext == pFirst) pNext = pNext->pNext;
        delete pFirst;
        pFirst = next_node;
        return;
    }
    TNode<TKey, TData>* prev_node = pFirst;
    while ((prev_node->pNext != nullptr) && (prev_node->pNext->key != key_))
    {
        prev_node = prev_node->pNext;
    }
    if (prev_node->pNext == nullptr) 
        throw exception("Key not found");
    TNode<TKey, TData>* next_node = prev_node->pNext->pNext;
    if (pCurrent == prev_node->pNext) pCurrent = nullptr;
    if (pNext == prev_node->pNext) pNext = prev_node->pNext->pNext;
    if (pPrevious == prev_node) pPrevious = prev_node;
    delete prev_node->pNext;
    prev_node->pNext = next_node;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Reset()
{
    pCurrent = pFirst;
    pPrevious = nullptr;
    if (pFirst != nullptr) pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
bool TList<TKey, TData>::IsEnded() const
{
    if (pCurrent == nullptr) return true;
    return false;
}

template <typename TKey, typename TData>
bool TList<TKey, TData>::IsEmpty() const
{
    if ((pCurrent == nullptr) && (pNext == nullptr)) return true;
    return false;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Next()
{
    if (IsEnded() == true) 
        throw exception("List is ended");
    if (pCurrent != nullptr)
    {
        pPrevious = pCurrent;
        pCurrent = pNext;
    }
    else
    {
        pCurrent = pNext;
    }
    if (pNext != nullptr)
    {
        pNext = pNext->pNext;
    }
    else
    {
        pNext = nullptr;
    }
}


template <typename TKey, typename TData>
ostream& operator<<(ostream& out, const TList<TKey, TData>& list)
{
    TNode<TKey, TData> *node = list.pFirst;
    while (node != nullptr)
    {
        out << *(node) << endl;
        node = node->pNext;
    }
    return out;
}

#endif