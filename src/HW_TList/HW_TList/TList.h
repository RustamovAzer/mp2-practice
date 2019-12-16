#ifndef _TLIST_H_
#define _TLIST_H_

#include "TNode.h"
#include <iostream>

using namespace std;

template <typename TKey, typename TData>
class TList
{
private:
    TNode<TKey, TData>* pFirst;
    TNode<TKey, TData>* pNext;
    TNode<TKey, TData>* pPrevious;
    TNode<TKey, TData>* pCurrent;

public:
    TList();
    TList(const TList<TKey, TData>& _tlist);
    TList(const TNode<TKey, TData>* _tnode);
    ~TList();


    TNode<TKey, TData>* Search(TKey);
    void InsertBegin(TKey _key, TData* _data);
    void Push(TKey _key, TData* _data);
    void InsertBefore(TKey _key, TKey _newKey, TData* _data);
    void InsertAfter(TKey _key, TKey _newKey, TData* _data);

    void Remove(TKey _key);

    void Reset();
    void Next();

    bool IsEnded() const;

    template<class TKey, class TData>
    friend ostream& operator<<(ostream& os, TList<TKey, TData>& tmp);
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
TList<TKey, TData>::TList(const TList& _tlist)
{
    pFirst = new TNode<TKey, TData>(*(_tlist.pFirst));
    TNode<TKey, TData>* _node = pFirst;
    TNode<TKey, TData>* tmp = _tlist.pFirst;
    while (tmp->pNext != nullptr)
    {
        _node->pNext = new TNode<TKey, TData>(*(tmp->pNext));
        _node = _node->pNext;
        tmp = tmp->pNext;
    }
    pPrevious = nullptr;    
    pCurrent = pFirst;
    pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _node)
{
    pFirst = new TNode<TKey, TData>(*_node);
    TNode<TKey, TData>* node = _node;
    TNode<TKey, TData>* tmp = pFirst;
    while (tmp->pNext != nullptr)
    {
        node->pNext = new TNode<TKey, TData>(*(tmp->pNext));
        node = node->pNext;
        tmp = tmp->pNext;
    }
    pPrevious = nullptr;
    pCurrent = pFirst;
    pNext = pFirst->pNext;
    
}

template <typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
    TNode<TKey, TData> *del = pFirst;
    TNode<TKey, TData> *next;
    while (del != nullptr)
    {
        next = del->pNext;
        delete del;
        del = next;
    }
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey _key)
{
    TNode<TKey, TData>* prev = pPrevious;
    TNode<TKey, TData>* next = pNext;
    TNode<TKey, TData>* curr = pCurrent;

    Reset();
    while (!IsEnded())
    {
        if (pCurrent->key == _key)
        {
            TNode<TKey, TData>* find = pCurrent;
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
void TList<TKey, TData>::InsertBegin(TKey _key, TData* _data)
{
    TNode<TKey, TData>* newFirstNode = new TNode<TKey, TData>(_key, _data, pFirst); 
    if (pCurrent == pFirst) pPrevious = newFirstNode;
    pFirst = newFirstNode;        
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Push(TKey _key, TData* _data)
{
    if (pFirst == nullptr)
    {
        pFirst = new TNode<TKey, TData>(_key, _data);
        pCurrent = pFirst;
        return;
    }
    TNode<TKey, TData>* prevToLastNode = pFirst;
    while (prevToLastNode->pNext != nullptr)
    {
        prevToLastNode = prevToLastNode->pNext;
    }
    prevToLastNode->pNext = new TNode<TKey, TData>(_key, _data);
    if (pCurrent == prevToLastNode) pNext = prevToLastNode->pNext;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey _key, TKey _newKey, TData* _data)
{
    if (pFirst == nullptr) return;
        //throw exception("List is empty");
    if (pFirst->key == _key)
    {
        InsertBegin(_newKey, _data);
        return;
    }
    TNode<TKey, TData>* prevNode = pFirst;
    while ((prevNode->pNext != nullptr) && (prevNode->pNext->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode->pNext == nullptr)
        throw exception("No node in list");
    
    TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_newKey, _data, prevNode->pNext);
    if (pCurrent == prevNode->pNext) pPrevious = newNode;
    prevNode->pNext = newNode;
    if (pCurrent == prevNode) pNext = newNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey _key, TKey _newKey, TData* _data)
{
    if (pFirst == nullptr) return;
        //throw exception("List is empty");
    TNode<TKey, TData>* prevNode = pFirst;
    while ((prevNode != nullptr) && (prevNode->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode == nullptr)
        throw exception("No node in list");
    TNode<TKey, TData>* nextNode = prevNode->pNext;
    TNode<TKey, TData>* newNode = new TNode<TKey, TData>(_newKey, _data);
    prevNode->pNext = newNode;
    newNode->pNext = nextNode;
    if (pCurrent == prevNode) pNext = newNode;
    if (pCurrent == nextNode) pPrevious = newNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Remove(TKey _key)
{
    if (pFirst == nullptr) return;
        //throw exception("List is empty");
    if (pFirst->key == _key)
    {
        bool FirstNodeWasCurrent = (pCurrent == pFirst);
        bool FirstNodeWasPrevious = (pPrevious == pFirst);
        TNode<TKey, TData>* nextNode = pFirst->pNext;
        delete pFirst;
        pFirst = nextNode;
        if (FirstNodeWasCurrent) pCurrent = nullptr;
        if (FirstNodeWasPrevious) pPrevious = nullptr;
        return;
    }
    TNode<TKey, TData>* prevNode = pFirst;
    while ((prevNode->pNext != nullptr) && (prevNode->pNext->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode->pNext == nullptr)       
        throw exception("No node in list");
    TNode<TKey, TData>* nextNode = prevNode->pNext->pNext;
    bool wasRemovedNodeCurrent = (pCurrent == prevNode->pNext);
    bool wasRemovedNodeNext = (pNext == prevNode->pNext);
    delete prevNode->pNext;;
    prevNode->pNext = nextNode;
    if (wasRemovedNodeCurrent) pCurrent = nullptr;
    if (wasRemovedNodeNext) pNext = nullptr;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Reset()
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
bool TList<TKey, TData>::IsEnded() const
{
    return (pNext == nullptr);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Next()
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
ostream& operator<<(ostream& os, TList<TKey, TData>& tmp)
{
    TNode<TKey, TData>* curr = tmp.pCurrent;
    TNode<TKey, TData>* prev = tmp.pPrevious;
    TNode<TKey, TData>* next = tmp.pNext;

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