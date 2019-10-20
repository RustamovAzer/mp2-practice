#ifndef _STACK_H_
#define _STACK_H_



using namespace std;

template<class ValType>
class TStack
{
private:
    size_t size, head;
    ValType* elems;
public:
    TStack(size_t);
    ~TStack();

    bool IsFull();
    bool IsEmpty();
    
    void Push(ValType _next);
    void Pop();
    ValType Top;

    TStack<ValType>& operator=(const TStack<ValType>& _tstack);
};

//------------------------------------------------

template<class ValType>
TStack<ValType>::TStack(size_t _size):size(_size), head(0)
{
    if (_size <=0) throw std::exception("Non-positive size")
    elems = new ValType[_size];
}

template<typename ValType>
TStack<ValType>::TStack(const TStack<ValType>& _stack) 
    : size(_stack.size), head(_stack.head)
{
    elems = new ValType[size];
    for (int i = 0; i < head; i++)
        elems[i] = _stack.elems[i];
}

template<class ValType>
TStack<ValType>::~TStack()
{
    head = 0;
    delete[] elems;
}

template<class ValType>
bool TStack<ValType>::IsFull()
{
    if (head == size)return true;
    return false;
}

template<class ValType>
bool TStack<ValType>::IsEmpty()
{
    if (head == 0)return true;
    return false;
}

template<class ValType>
void TStack<ValType>::Push(ValType _next)
{
    if (IsFull)throw "Stack is full";
    elems[head++] = _next;
}

template<class ValType>
void TStack<ValType>::Pop()
{
    if (IsEmpty)throw "Stack is empty";
    return elems[--head];
}



template<typename ValType>
ValType Stack<ValType>::Top() const
{
    if (IsEmpty()) throw std::exception("Stack is empty")
    return elems[head - 1];
}

template<typename ValType>
TStack<ValType>& TStack<ValType>::operator=(const TStack<ValType>& _tstack)
{
    if (this == &_tstack)
        return *this;
    if (size != _tstack.size)
    {
        delete elems;
        size = _tstack.size;
        elems = new ValType[size];
    }
    head = _tstack.head;
    for (int i = 0; i < size; i++)
        elems[i] = _tstack.elems[i];
    return *this;
}

};

#endif