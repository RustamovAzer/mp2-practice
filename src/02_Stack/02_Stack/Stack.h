#ifndef _STACK_H_
#define _STACK_H_

using namespace std;

template<class ValType>
class Stack
{
private:
    size_t size, head;
    ValType* elems;
public:
    Stack(size_t);
    Stack(const Stack&);
    ~Stack();

    bool IsFull();
    bool IsEmpty();
    
    void Push(ValType _next);
    void Pop();
    ValType Top();

    Stack<ValType>& operator=(const Stack<ValType>& _Stack);
};

//------------------------------------------------

template<class ValType>
Stack<ValType>::Stack(size_t _size):size(_size), head(0)
{
    if (_size <= 0) throw exception("Неположительный размер");
    elems = new ValType[_size];
}

template<typename ValType>
Stack<ValType>::Stack(const Stack<ValType>& _stack)
    : size(_stack.size), head(_stack.head)
{
    elems = new ValType[size];
    for (int i = 0; i < head; i++)
        elems[i] = _stack.elems[i];
}

template<class ValType>
Stack<ValType>::~Stack()
{
    head = 0;
    delete[] elems;
}

template<class ValType>
bool Stack<ValType>::IsFull()
{
    if (head == size)return true;
    return false;
}

template<class ValType>
bool Stack<ValType>::IsEmpty()
{
    if (head == 0)return true;
    return false;
}

template<class ValType>
void Stack<ValType>::Push(ValType _next)
{
    if (IsFull()) throw "Стек полон";
    elems[head++] = _next;
}

template<class ValType>
void Stack<ValType>::Pop()
{
    if (IsEmpty()) throw exception("Стек пуст");
    --head;
}

template<class ValType>
ValType Stack<ValType>::Top()
{
    if (IsEmpty()) throw exception("Стек пуст");
        return elems[head - 1];
}



template<class ValType>
Stack<ValType>& Stack<ValType>::operator=(const Stack<ValType>& _Stack)
{
    if (this == &_Stack)
        return *this;
    if (size != _Stack.size)
    {
        delete elems;
        size = _Stack.size;
        elems = new ValType[size];
    }
    head = _Stack.head;
    for (int i = 0; i < size; i++)
        elems[i] = _Stack.elems[i];
    return *this;
}



#endif