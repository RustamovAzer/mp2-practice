


template<class TData, class TKey>
class TNode
{
public:
    TData* pData;
    TKey key;
    TNode* pNext;

    TNode(TData*, TKey);
    TNode(const TNode&);

};

//------------------------------------

template<class TData, class TKey>
TNode<TData, TKey>::TNode(TData* _pData, TKey _key) : pData(_pData), key(_key), pNext(0)
{
}

template<class TData, class TKey>
TNode<TData, TKey>::TNode(const TNode<TData, TKey> &node) : pData(node.pData), key(node.key), pNext(0)
{
}

template<class TKey, class TData>
TNode<TData, TKey>::~TNode()
{
    Key = 0;
    data = 0;
    pNext = 0;
};