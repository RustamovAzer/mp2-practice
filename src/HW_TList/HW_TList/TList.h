
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
    void Next;
    void Reset;
    TNode<TData, TKey>* Search(TKey);
    void Back(TData*, TKey);
    void Push(TData*, TKey);
    void InsertAfter(TKey, TData*, TKey);
    void InsertBefore(TKey, TData*, TKey);
    void Remove(TKey);
};