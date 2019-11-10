#include <exception>
#include "TNode.h"



template<class TData, class TKey>
class TList
{
private:
    TNode<TData, TKey>* pFirst;
    TNode<TData, TKey>* pPrev;
    TNode<TData, TKey>* pCurr;
    TNode<TData, TKey>* pNext;
public:
    TList();
    TList(TNode<TData, TKey>*);
    TList(const TList&);
    ~TList();
    bool IsEnded() const;
    void Next();
    void Reset();
    TNode<TData, TKey>* Search(TKey);
    void Back(TData*, TKey);
    void Push(TData*, TKey);
    void InsertAfter(TKey, TData*, TKey);
    void InsertBefore(TKey, TData*, TKey);
    void Remove(TKey);

    void Print();
};
//-------------------------------------------
template<class TKey, class TData>
TList<TKey, TData>::TList():pFirst(0), pCurr(0),pNext(0)
{
}
template<class TKey, class TData>
TList<TKey, TData>::TList(const TList& _list): pFirst(0),pPrev(0), pCurr(0), pNext(0)
{

    if (_list.pFirst == 0)
    {
        pFirst = 0;
    }
    else
    {
        pFirst = new TNode<TKey, TData>(*_list.pFirst);
        pFirst->pNext = 0;
        pCurr = pFirst;

        _list.Reset();

        while (!_list.IsEnded())
        {
            _list.Next();
            pCurr->pNext = new TNode<TKey, TData>(*_list.pCurrent);

            pPrev = pCurr;
            pCurr = pCurr->pNext;
            pNext = pCurr->pNext;
            pNext = 0;
        }
    }
};
template<class TKey, class TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _first) : pFirst(_first), pPrev(0), pCurr(0), pNext(0)
{
}

template<class TKey, class TData>
TList<TKey, TData>::~TList()
{
    Reset();
    while (!IsEnded())
    {
        Next();
        delete pPrev;
    }

    delete pCurr;
    pFirst = 0;
    pCurr = 0;
    pPrev = 0;
    pNext = 0;
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey _key)
{
    Reset();

    while (!IsEnded())
    {
        if (pCurr->Key == Key)
            return pCurr;
        Next();
    }

    Reset();
    return nullptr;
};
template<class TKey, class TData>
void TList<TKey, TData>::Push(TData* _data,TKey Key )
{
    if (pCurr != nullptr)
        Reset();
    TNode<TKey, TData>* node = new TNode<TKey, TData>(Key, _data, pFirst);
    pNext = pFirst;
    pFirst = node;
    pCurr = pFirst;
    Reset();
};

template<class TKey, class TData>
void TList<TKey, TData>::Back(TData* _data, TKey Key)
{
    Reset();
    while (!IsEnded())
        Next();

    TNode<TKey, TData>* node = new TNode<TKey, TData>(Key, _data);
    pCurr->pNext = node;
    Reset();
};
template<class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey _Key, TData* _data, TKey newKey)
{
    Reset();

    TNode<TKey, TData>* node = Search(_Key);
    if (node == nullptr)
        throw exception("unable to find given key");

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data);
    pCurr->pNext = _node;
    pPrev = pCurr;
    pCurr = node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey Key, TData* _data, TKey newKey)
{
    Reset();

    if (IsEnded())
    {
        InsertToStart(newKey, _data);
        return;
    }

    TNode<TKey, TData>* node = Search(Key);
    if (node == nullptr)
        throw exception("unable to find given key");

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data, pCurr);
    pNext = pCurr;
    pPrev->pNext = _node;
    pCurr = _node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Remove(TKey _Key)
{
    Reset();

    if (!pFirst)
        throw exception("List is empty");

    if (pFirst->Key == Key)
    {
        delete pFirst;
        pFirst = pNext;
        Reset();
        return;
    }

    TNode<TKey, TData>* node = Search(_Key);

    if (node == nullptr)
        throw exception("unable to find given key");

    pPrev->pNext = pNext;
    delete node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Reset()
{
    pCurr = pFirst;
    pPrev = nullptr;
    pNext = pCurr->pNext;
};

template<class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
    if (pFirst == nullptr)
        return true;
    return false;
};

template<class TKey, class TData>
void TList<TKey, TData>::Next()
{
    pPrev = pCurr;
    pCurr = pNext;

    if (pCurr)
        pNext = pCurr->pNext;
    else pNext = nullptr;
};

template<class TKey, class TData>
void TList<TKey, TData>::Print()
{
    Reset();

    while (!IsEnded())
    {
        cout << pCurr->Key;
        Next();
    }
};