#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include <iostream>
#include <string>

using namespace std;

class Variables
{
    struct Variable 
    {
        string name;
        double value;
    };
    Variable* values;
    int size;
    int head;
public:
    Variables(int size_ = 10);
    Variables(const Variables& temp);
    ~Variables();

    void Push(const string& _name, double _value);
    int Count(const string& _name) const;

    const double operator[](const string& _name) const;
    const Variables& operator=(const Variables& temp);
};


#endif // !__VARIABLES_H__