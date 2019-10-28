#include "Variables.h"

using namespace std;

Variables::Variables(int _countOFVariables, const string* _variables)
{
    countOfVariables = _countOFVariables;
    variables = new string[countOfVariables];
    for (int i = 0; i < countOfVariables; i++)
    {
        variables[i] = _variables[i];
        cout << "Set the value of the variable: " << variables[i] << " = ";
        cin >> values[i];
    }
}

void Variables::setValues()
{
    for (int i = 0; i < countOfVariables; i++)
    {
        cout << "Set the value of the variable: " << variables[i] << " = ";
        cin >> values[i];
    }
}

double & Variables::operator[](int index)
{
    return values[index];
}

const double & Variables::operator[](int index) const
{
    return values[index];
}

Variables::~Variables()
{
    if (variables != nullptr)
        delete[] variables;
}