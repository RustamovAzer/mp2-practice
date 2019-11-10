#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include <iostream>
#include <string>

using namespace std;

class Variables
{
public:
    int countOfVariables;
    string* variables;
    double* values;

    Variables(const string* _variables);

    void setValues();

    double& operator[](int index);
    const double& operator[](int index) const;

    ~Variables();

private:
    static bool isNumber(const string& _str);
};


#endif // !__VARIABLES_H__