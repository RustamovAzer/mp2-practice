
#include "Variables.h"

using namespace std;

Variables::Variables(int _size)
{
    if (_size == 0) throw exception("Incorrect size");
    size = _size;
    head = 0;
    values = new Variable[size];
}
Variables::Variables(const Variables& temp)
{
    size = temp.size;
    head = temp.head;
    values = new Variable[size];
    for (int i = 0; i < head; i++)
    {
        values[i] = temp.values[i];
    }
}

Variables::~Variables()
{
    delete[] values;
}

void Variables::Push(const string& _name, double value_)
{
    if (head == size)
    {
        Variable* temp = new Variable[size + 10];
        for (int i = 0; i < size; i++)
        {
            temp[i] = values[i];
        }
        delete[] values;
        values = temp;
        size += 10;
    }
    values[head].name = _name;
    values[head].value = value_;
    head++;
}

int Variables::Count(const string& _name) const
{
    int result = 0;
    for (int i = 0; i < head; i++)
    {
        if (values[i].name == _name) result++;
    }
    return result;
}

const double Variables::operator[](const string& _name) const
{
    for (int i = 0; i < head; i++)
    {
        if (values[i].name == _name) return values[i].value;
    }
    //throw exception("Unable to find");
}

const Variables& Variables::operator=(const Variables& temp)
{
    if (size != temp.size) delete[] values;
    size = temp.size;
    head = temp.head;
    values = new Variable[size];
    for (int i = 0; i < head; i++)
    {
        values[i] = temp.values[i];
    }
    return *this;
}