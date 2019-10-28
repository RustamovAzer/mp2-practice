#ifndef _PostfixForm_H_
#define _PostfixForm_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Stack.h"
#include "Variables.h"

using namespace std;

static class PostfixForm
{
private:
    static int countOfOperands;
    static string *operands;
    static string postfixForm;



public:
    static string ConvertToPostfixForm(const string& _expression);
    static double Calculate(const string& _postfixForm, const Variables& _var);
    static int getPriorityOfOperator(const char _operator);
    static void Clear();

    static string*& getOperands();
    static int getCountOfOperands();

private:
    static bool isNumber(const string& _str);
};
#endif _PostfixForm_H_

