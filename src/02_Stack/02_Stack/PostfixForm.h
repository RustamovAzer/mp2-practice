#ifndef _PostfixForm_H_
#define _PostfixForm_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Stack.h"
#include "Variables.h"


static class PostfixForm
{
private:
    static int countOfOperands;
    static std::string *operands;
    static std::string postfixForm;



public:
    static std::string ConvertToPostfixForm(const std::string& _expression);
    static double Calculate(const std::string& _postfixForm, const Variables & _var);
    static int getPriorityOfOperator(const char _operator);
    static void Clear();

    static std::string*& getOperands();
    static int getCountOfOperands();

private:
    static bool isNumber(const std::string& _str);
};
#endif _PostfixForm_H_

