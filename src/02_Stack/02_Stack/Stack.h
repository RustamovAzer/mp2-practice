#ifndef _STACK_H_
#define _STACK_H_



using namespace std;

template<class ValueType>
class TStack
{
private:
    size_t size, top;
    ValueType* elems;
public:
    TStack(size_t);
    ~TStack();

    bool IsFull();
    bool IsEmpty();
    
    void Push(ValueType _next);
    ValueType Pop();

};

//------------------------------------------------

template<class ValueType>
TStack<ValueType>::TStack(size_t _size)
{
    top = 0;
    elems = new ValueType[_size];
}

template<class ValueType>
TStack<ValueType>::~TStack()
{
    top = 0;
    delete[] elems;
}

template<class ValueType>
bool TStack<ValueType>::IsFull()
{
    if (top == size)return true;
    return false;
}

template<class ValueType>
bool TStack<ValueType>::IsEmpty()
{
    if (top == 0)return true;
    return false;
}

template<class ValueType>
void TStack<ValueType>::Push(ValueType _next)
{
    if (IsFull)throw "Stack is full";
    elems[top++] = _next;
}

template<class ValueType>
inline ValueType TStack<ValueType>::Pop()
{
    if (IsEmpty)throw "Stack is empty";
    return elems[--top];
}

#endif