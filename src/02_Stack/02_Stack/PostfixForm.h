#ifndef _PostfixForm_H_
#define _PostfixForm_H_

#include <cstdlib>
#include "Stack.h"
#include "Variables.h"


using namespace std;

static class PostfixForm
{
private:
    static int getPriorityOfOperator(const char _operator);

public:
    static string ConvertToPostfixForm(const string& _expression);
    static Variables GetVariables(const string& input);
    static double Calculate(const string& _PostfixForm, const Variables & _var);

};
#endif _PostfixForm_H_

