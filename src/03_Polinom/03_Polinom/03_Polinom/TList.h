#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_

#include "TMonom.h"
#include <iostream>

using namespace std;



//template <typename TKey, typename TData>
template<template <typename TKey, typename TData> class TMonom >
class TPolinom
{
private:
    TMonom<TMonom<TKey, TData> >* pFirst;
    TMonom<TMonom<TKey, TData> >* pNext;
    TMonom<TMonom<TKey, TData> >* pPrevious;
    TMonom<TMonom<TKey, TData> >* pCurrent;

public:
    TPolinom();
    TPolinom(const TPolinom<TMonom<TKey, TData> >& _tlist);
    TPolinom(const TMonom<TMonom<TKey, TData> >* _TMonom);
    ~TPolinom();


    TMonom<TMonom<TKey, TData> >* Search(TKey);
    void InsertBegin(TKey _key, TData _data);
    void Push(TKey _key, TData _data);
    void InsertBefore(TKey _key, TKey _newKey, TData _data);
    void InsertAfter(TKey _key, TKey _newKey, TData _data);

    void Remove(TKey _key);

    void Reset();
    void Next();

    bool IsEnded() const;

    template<class TKey, class TData>
    friend ostream& operator<<(ostream& os, TPolinom<TMonom<TKey, TData> >& tmp);
};

template <typename TKey, typename TData>
TPolinom<TMonom<TKey, TData> >::TPolinom()
{
    pFirst = nullptr;
    pPrevious = nullptr;
    pNext = nullptr;
    pCurrent = nullptr;
}

template <typename TKey, typename TData>
TPolinom<TMonom<TKey, TData> >::TPolinom(const TPolinom& _tlist)
{
    pFirst = new TMonom<TMonom<TKey, TData> >(*(_tlist.pFirst));
    TMonom<TMonom<TKey, TData> >* _node = pFirst;
    TMonom<TMonom<TKey, TData> >* tmp = _tlist.pFirst;
    while (tmp->pNext != nullptr)
    {
        _node->pNext = new TMonom<TMonom<TKey, TData> >(*(tmp->pNext));
        _node = _node->pNext;
        tmp = tmp->pNext;
    }
    pPrevious = nullptr;    
    pCurrent = pFirst;
    pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
TPolinom<TMonom<TKey, TData> >::TPolinom(const TMonom<TMonom<TKey, TData> >* _node)
{
    pFirst = new TMonom<TMonom<TKey, TData> >(*_node));
    TMonom<TMonom<TKey, TData> >* node = _node;
    TMonom<TMonom<TKey, TData> >* tmp = pFirst;
    while (tmp->pNext != nullptr)
    {
        node->pNext = new TMonom<TMonom<TKey, TData> >(*(tmp->pNext));
        node = node->pNext;
        tmp = tmp->pNext;
    }
    pPrevious = nullptr;
    pCurrent = pFirst;
    pNext = pFirst->pNext;
    
}

template <typename TKey, typename TData>
TPolinom<TMonom<TKey, TData> >::~TPolinom()
{
    TMonom<TMonom<TKey, TData> > *del = pFirst;
    TMonom<TMonom<TKey, TData> > *next;
    while (del != nullptr)
    {
        next = del->pNext;
        delete del;
        del = next;
    }
}

template<class TKey, class TData>
TMonom<TMonom<TKey, TData> >* TPolinom<TMonom<TKey, TData> >::Search(TKey _key)
{
    TMonom<TMonom<TKey, TData> >* prev = pPrevious;
    TMonom<TMonom<TKey, TData> >* next = pNext;
    TMonom<TMonom<TKey, TData> >* curr = pCurrent;

    Reset();
    while (!IsEnded())
    {
        if (pCurrent->key == _key)
        {
            TMonom<TMonom<TKey, TData> >* find = pCurrent;
            pCurrent = curr;
            pPrevious = prev;
            pNext = next;
            return find;
        }
        Next();
    };

    pPrevious = prev;
    pNext = next;
    pCurrent = curr;

    return nullptr;
};

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::InsertBegin(TKey _key, TData _data)
{
    TMonom<TMonom<TKey, TData> >* newFirstMonom = new TMonom<TMonom<TKey, TData> >(_key, _data, pFirst);
    if (pCurrent == pFirst) pPrevious = newFirstMonom;
    pFirst = newFirstMonom;        
}

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::Push(TKey _key, TData _data)
{
    if (pFirst == nullptr)
    {
        pFirst = new TMonom<TMonom<TKey, TData> >(_key, _data);
        pCurrent = pFirst;
        return;
    }
    TMonom<TMonom<TKey, TData> >* prevToLastMonom = pFirst;
    while (prevToLastMonom->pNext != nullptr)
    {
        prevToLastMonom = prevToLastMonom->pNext;
    }
    prevToLastMonom->pNext = new TMonom<TMonom<TKey, TData> >(_key, _data);
    if (pCurrent == prevToLastMonom) pNext = prevToLastMonom->pNext;
}

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::InsertBefore(TKey _key, TKey _newKey, TData _data)
{
    if (pFirst == nullptr) 
        throw exception("List is empty");
    if (pFirst->key == _key)
    {
        InsertBegin(_newKey, _data);
        return;
    }
    TMonom<TMonom<TKey, TData> >* prevNode = pFirst;
    while ((prevNode->pNext != nullptr) && (prevNode->pNext->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode->pNext == nullptr)
        throw exception("No node in list");
    
    TMonom<TMonom<TKey, TData> >* newNode = new TMonom<TMonom<TKey, TData> >(_newKey, _data, prevNode->pNext);
    if (pCurrent == prevNode->pNext) pPrevious = newNode;
    prevNode->pNext = newNode;
    if (pCurrent == prevNode) pNext = newNode;
}

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::InsertAfter(TKey _key, TKey _newKey, TData _data)
{
    if (pFirst == nullptr) return;
        throw exception("List is empty");
    TMonom<TMonom<TKey, TData> >* prevNode = pFirst;
    while ((prevNode != nullptr) && (prevNode->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode == nullptr)
        throw exception("No node in list");
    TMonom<TMonom<TKey, TData> >* nextMonom = prevNode->pNext;
    TMonom<TMonom<TKey, TData> >* newNode = new TMonom<TMonom<TKey, TData> >(_newKey, _data);
    prevNode->pNext = newNode;
    newNode->pNext = nextMonom;
    if (pCurrent == prevNode) pNext = newNode;
    if (pCurrent == nextMonom) pPrevious = newNode;
}

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::Remove(TKey _key)
{
    if (pFirst == nullptr) return;
        throw exception("List is empty");
    if (pFirst->key == _key)
    {
        bool FirstMonomWasCurrent = (pCurrent == pFirst);
        bool FirstMonomWasPrevious = (pPrevious == pFirst);
        TMonom<TMonom<TKey, TData> >* nextMonom = pFirst->pNext;
        delete pFirst;
        pFirst = nextMonom;
        if (FirstMonomWasCurrent) pCurrent = nullptr;
        if (FirstMonomWasPrevious) pPrevious = nullptr;
        return;
    }
    TMonom<TMonom<TKey, TData> >* prevNode = pFirst;
    while ((prevNode->pNext != nullptr) && (prevNode->pNext->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode->pNext == nullptr)       
        throw exception("No node in list");
    TMonom<TMonom<TKey, TData> >* nextMonom = prevNode->pNext->pNext;
    bool wasRemovedNodeCurrent = (pCurrent == prevNode->pNext);
    bool wasRemovedNodeNext = (pNext == prevNode->pNext);
    delete prevNode->pNext;
    prevNode->pNext = nextMonom;
    if (wasRemovedNodeCurrent) pCurrent = nullptr;
    if (wasRemovedNodeNext) pNext = nullptr;
}

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::Reset()
{
    pCurrent = pFirst;
    pPrevious = nullptr;
    if (pFirst)
    {
        pNext = pFirst->pNext;
    }
    else
    {
        pNext = nullptr;
    }
}

template <typename TKey, typename TData>
bool TPolinom<TMonom<TKey, TData> >::IsEnded() const
{
    return (pNext == nullptr);
}

template <typename TKey, typename TData>
void TPolinom<TMonom<TKey, TData> >::Next()
{
    if (IsEnded())
        throw exception("No node in list");
    if (pCurrent != nullptr)
    {
        pPrevious = pCurrent;
        pCurrent = pNext;
        pNext = pNext->pNext;
    }
    else
    {
        if (pNext == 0)
        {
            pCurrent = pNext;
        }
        pPrevious = nullptr;
        pNext = pNext->pNext;
    }
}
template<class TKey, class TData>
ostream& operator<<(ostream& os, TPolinom<TMonom<TKey, TData> >& tmp)
{
    TMonom<TMonom<TKey, TData> >* curr = tmp.pCurrent;
    TMonom<TMonom<TKey, TData> >* prev = tmp.pPrevious;
    TMonom<TMonom<TKey, TData> >* next = tmp.pNext;

    tmp.Reset();

    while (!tmp.IsEnded())
    {
        os << tmp.pCurrent->key << " ";
        tmp.Next();
    }

    os << tmp.pCurrent->key << " " << endl;

    tmp.pCurrent = curr;
    tmp.pPrevious = prev;
    tmp.pNext = next;

    return os;
}


#endif