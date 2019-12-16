#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_

#include "TMonom.h"
#include <iostream>
#include <string>

using namespace std;

template <typename TKey, typename TData>
class TPolinom
{
private:
    TMonom<TKey, TData>* pFirst;
    TMonom<TKey, TData>* pNext;
    TMonom<TKey, TData>* pPrevious;
    TMonom<TKey, TData>* pCurrent;

public:
    TPolinom();
    TPolinom(const TPolinom<TKey, TData>& _tlist);
    TPolinom(const TMonom<TKey, TData>* _tnode);
    TPolinom(const string& _expression);
    ~TPolinom();


    TMonom<TKey, TData>* Search(TKey);
    void InsertBegin(TKey _key, TData _data);
    void Push(TKey _key, TData _data);
    void InsertBefore(TKey _key, TKey _newKey, TData _data);
    void InsertAfter(TKey _key, TKey _newKey, TData _data);

    void Remove(TKey _key);

    void Reset();
    void Next();

    bool IsEnded() const;

    template<class TKey, class TData>
    friend ostream& operator<<(ostream& os, TPolinom<TKey, TData>& tmp);
};

template <typename TKey, typename TData>
TPolinom<TKey, TData>::TPolinom()
{
    pFirst = nullptr;
    pPrevious = nullptr;
    pNext = nullptr;
    pCurrent = nullptr;
}

template <typename TKey, typename TData>
TPolinom<TKey, TData>::TPolinom(const TPolinom& _tlist)
{
    pFirst = new TMonom<TKey, TData>(*(_tlist.pFirst));
    TMonom<TKey, TData>* _node = pFirst;
    TMonom<TKey, TData>* tmp = _tlist.pFirst;
    while (tmp->pNext != nullptr)
    {
        _node->pNext = new TMonom<TKey, TData>(*(tmp->pNext));
        _node = _node->pNext;
        tmp = tmp->pNext;
    }
    pPrevious = nullptr;
    pCurrent = pFirst;
    pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
TPolinom<TKey, TData>::TPolinom(const TMonom<TKey, TData>* _node)
{
    pFirst = new TMonom<TKey, TData>(*_node));
    TMonom<TKey, TData>* node = _node;
    TMonom<TKey, TData>* tmp = pFirst;
    while (tmp->pNext != nullptr)
    {
        node->pNext = new TMonom<TKey, TData>(*(tmp->pNext));
        node = node->pNext;
        tmp = tmp->pNext;
    }
    pPrevious = nullptr;
    pCurrent = pFirst;
    pNext = pFirst->pNext;

}

template<typename TKey, typename TData>
TPolinom<TKey, TData>::TPolinom(const string & _expression)
{

    string monom;
    string buffer;

    size_t foundoperator = _expression.find_first_of("+-");
    size_t foundbegin = _expression.find_first_of("1234567890xyz^+-");
    size_t foundend = _expression.find_first_not_of("1234567890.xyz^+-");
    monom = foundoperator + _expression.substr(foundbegin, foundend - foundbegin);
    // создание монома

}

template <typename TKey, typename TData>
TPolinom<TKey, TData>::~TPolinom()
{
    TMonom<TKey, TData> *del = pFirst;
    TMonom<TKey, TData> *next;
    while (del != nullptr)
    {
        next = del->pNext;
        delete del;
        del = next;
    }
}

template<class TKey, class TData>
TMonom<TKey, TData>* TPolinom<TKey, TData>::Search(TKey _key)
{
    TMonom<TKey, TData>* prev = pPrevious;
    TMonom<TKey, TData>* next = pNext;
    TMonom<TKey, TData>* curr = pCurrent;

    Reset();
    while (!IsEnded())
    {
        if (pCurrent->key == _key)
        {
            TMonom<TKey, TData>* find = pCurrent;
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
void TPolinom<TKey, TData>::InsertBegin(TKey _key, TData _data)
{
    TMonom<TKey, TData>* newFirstNode = new TMonom<TKey, TData>(_key, _data, pFirst);
    if (pCurrent == pFirst) pPrevious = newFirstNode;
    pFirst = newFirstNode;
}

template <typename TKey, typename TData>
void TPolinom<TKey, TData>::Push(TKey _key, TData _data)
{
    if (pFirst == nullptr)
    {
        pFirst = new TMonom<TKey, TData>(_key, _data);
        pCurrent = pFirst;
        return;
    }
    TMonom<TKey, TData>* prevToLastNode = pFirst;
    while (prevToLastNode->pNext != nullptr)
    {
        prevToLastNode = prevToLastNode->pNext;
    }
    prevToLastNode->pNext = new TMonom<TKey, TData>(_key, _data);
    if (pCurrent == prevToLastNode) pNext = prevToLastNode->pNext;
}

template <typename TKey, typename TData>
void TPolinom<TKey, TData>::InsertBefore(TKey _key, TKey _newKey, TData _data)
{
    if (pFirst == nullptr)
        throw exception("List is empty");
    if (pFirst->key == _key)
    {
        InsertBegin(_newKey, _data);
        return;
    }
    TMonom<TKey, TData>* prevNode = pFirst;
    while ((prevNode->pNext != nullptr) && (prevNode->pNext->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode->pNext == nullptr)
        throw exception("No node in list");

    TMonom<TKey, TData>* newNode = new TMonom<TKey, TData>(_newKey, _data, prevNode->pNext);
    if (pCurrent == prevNode->pNext) pPrevious = newNode;
    prevNode->pNext = newNode;
    if (pCurrent == prevNode) pNext = newNode;
}

template <typename TKey, typename TData>
void TPolinom<TKey, TData>::InsertAfter(TKey _key, TKey _newKey, TData _data)
{
    if (pFirst == nullptr) return;
    throw exception("List is empty");
    TMonom<TKey, TData>* prevNode = pFirst;
    while ((prevNode != nullptr) && (prevNode->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode == nullptr)
        throw exception("No node in list");
    TMonom<TKey, TData>* nextNode = prevNode->pNext;
    TMonom<TKey, TData>* newNode = new TMonom<TKey, TData>(_newKey, _data);
    prevNode->pNext = newNode;
    newNode->pNext = nextNode;
    if (pCurrent == prevNode) pNext = newNode;
    if (pCurrent == nextNode) pPrevious = newNode;
}

template <typename TKey, typename TData>
void TPolinom<TKey, TData>::Remove(TKey _key)
{
    if (pFirst == nullptr) return;
    throw exception("List is empty");
    if (pFirst->key == _key)
    {
        bool FirstNodeWasCurrent = (pCurrent == pFirst);
        bool FirstNodeWasPrevious = (pPrevious == pFirst);
        TMonom<TKey, TData>* nextNode = pFirst->pNext;
        delete pFirst;
        pFirst = nextNode;
        if (FirstNodeWasCurrent) pCurrent = nullptr;
        if (FirstNodeWasPrevious) pPrevious = nullptr;
        return;
    }
    TMonom<TKey, TData>* prevNode = pFirst;
    while ((prevNode->pNext != nullptr) && (prevNode->pNext->key != _key))
    {
        prevNode = prevNode->pNext;
    }
    if (prevNode->pNext == nullptr)
        throw exception("No node in list");
    TMonom<TKey, TData>* nextNode = prevNode->pNext->pNext;
    bool wasRemovedNodeCurrent = (pCurrent == prevNode->pNext);
    bool wasRemovedNodeNext = (pNext == prevNode->pNext);
    delete prevNode->pNext;
    prevNode->pNext = nextNode;
    if (wasRemovedNodeCurrent) pCurrent = nullptr;
    if (wasRemovedNodeNext) pNext = nullptr;
}

template <typename TKey, typename TData>
void TPolinom<TKey, TData>::Reset()
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
bool TPolinom<TKey, TData>::IsEnded() const
{
    return (pNext == nullptr);
}

template <typename TKey, typename TData>
void TPolinom<TKey, TData>::Next()
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
ostream& operator<<(ostream& os, TPolinom<TKey, TData>& tmp)
{
    TMonom<TKey, TData>* curr = tmp.pCurrent;
    TMonom<TKey, TData>* prev = tmp.pPrevious;
    TMonom<TKey, TData>* next = tmp.pNext;

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