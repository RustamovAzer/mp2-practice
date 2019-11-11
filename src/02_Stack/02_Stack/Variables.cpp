#include "Variables.h"
using namespace std;

Variables::Variables(const string* _variables)
{
    int countOfOperands = 0;
    for (int i = 0; _variables[i] != " "; i++)
        countOfOperands++;
    countOfVariables = countOfOperands;

    values = new double[countOfVariables];
    variables = new string[countOfVariables];

    for (int i = 0; i < countOfVariables; i++)
    {
        variables[i] = _variables[i];

        bool cont = false;
        for (int j = 0; j < i; j++)
            if (variables[i] == variables[j]) {
                values[i] = values[j];
                cont = true;
                break;
            }
        if (cont) continue;

        if (isNumber(variables[i]))
            values[i] = stod(variables[i], 0);
        else {
            cout << "Введите значение переменной: " << variables[i] << " = ";
            cin >> values[i];
        }
    }
}
void Variables::setValues()
{
    for (int i = 0; i < countOfVariables; i++)
    {
        cout << "Введите значение переменной " << variables[i] << ": ";
        cin >> values[i];
    }
}

double & Variables::operator[](int index)
{
    return values[index];
}

const double & Variables::operator[](const string& _var) const //
{
    bool found = false;
    for (size_t i = 0; i < countOfVariables; i++)
    {
        if (variables[i] == _var)
        {
            return values[i];
            found = true;
        }
    }
    if (!found) throw exception("Не найдена переменная");

}

bool Variables::isNumber(const string& _str)
{
    return ((!_str.empty()) && (_str.find_first_not_of("0123456789.") == _str.npos));
}

Variables::~Variables()
{
    if (variables != nullptr)
        delete[] variables;
    if (values != nullptr)
        delete[] values;
}