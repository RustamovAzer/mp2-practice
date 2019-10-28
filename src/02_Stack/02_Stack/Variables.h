#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include "iostream"
#include "string"

class Variables
{
public:
    int countOfVariables;
    string* variables;
    double* values;

    Variables(int _countOFVariables, const string* _variables);

    void setValues();

    double& operator[](int index);
    const double& operator[](int index) const;

    ~Variables();

private:

};


#endif // !__VARIABLES_H__