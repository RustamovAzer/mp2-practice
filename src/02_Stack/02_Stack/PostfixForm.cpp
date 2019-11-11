#include <string>
#include <iostream>
#include "PostfixForm.h"

string *PostfixForm::operands;

using namespace std;

string PostfixForm::ConvertToPostfixForm(const string & _expression)
{
    string *_operands = new string[_expression.length()];
    string buffer;
    int lengthOfExpression = _expression.length();
    int countOfOperators = 0;
    int countOfOperands = 0;
    int countOfLeftBrackets = 0;
    int countOfRightBrackets = 0;
    char lastSymbol = 0;
    int indexOfOperand = 0;

    Stack<char> operators(lengthOfExpression);
    Stack<string> operands(lengthOfExpression);

    for (int i = 0; i < lengthOfExpression; i++)
    {
        if (buffer.length() != 0)
        {
            if ((_expression[i] == '+') || (_expression[i] == '-')
                || (_expression[i] == '*') || (_expression[i] == '/')
                || (_expression[i] == '(') || (_expression[i] == ')')
                || (_expression[i] == ' '))
            {
                countOfOperands++;
                operands.Push(buffer);
                {
                    int k = 0;
                    while ((k < indexOfOperand) &&
                        (_operands[k++] != _operands[indexOfOperand])) {
                    };
                    if (k == indexOfOperand)
                        _operands[indexOfOperand++] = buffer;
                }
                buffer.clear();
            }
        }

        if (_expression[i] == ' ');
        else if ((_expression[i] != '+') && (_expression[i] != '-')
            && (_expression[i] != '*') && (_expression[i] != '/')
            && (_expression[i] != '(') && (_expression[i] != ')'))
        {
            if (countOfOperands == (countOfOperators + 1))
            throw exception("Неверное выражение");
            buffer.push_back(_expression[i]);
            if (i == (lengthOfExpression - 1))
            {
                countOfOperands++;
                operands.Push(buffer);
                {
                    int k = 0;
                    while ((k < indexOfOperand) &&
                        (_operands[k++] != _operands[indexOfOperand])) {
                    };
                    if (k == indexOfOperand)
                        _operands[indexOfOperand++] = buffer;
                }
                buffer.clear();
            }
        }
        else if (_expression[i] == '(')
        {
            if ((lastSymbol != '+') && (lastSymbol != '-')
                && (lastSymbol != '*') && (lastSymbol != '/')
                && (lastSymbol != ' ') && (lastSymbol != '(')
                && (lastSymbol != 0))   
                throw exception("Неверное выражение");
            countOfLeftBrackets++;
            operators.Push(_expression[i]);
        }
        else if (_expression[i] == ')')
        {
            if ((lastSymbol == '+') || (lastSymbol == '-')
                || (lastSymbol == '*') || (lastSymbol == '/')
                || (lastSymbol == '('))
                throw exception("Неверное выражение");
            countOfRightBrackets++;
            while (operators.Top() != '(')
            {
                string tmp;
                try
                {
                    tmp.push_back(operators.Top());
                    operators.Pop();
                    operands.Push(tmp);
                }
                catch (exception e)
                {
                    throw exception("Неверное выражение");
                }
            }
            operators.Pop();
        }
        else if (operators.IsEmpty())
        {
            if (lastSymbol == 0) throw exception("Неверное выражение");
            operators.Push(_expression[i]);
            countOfOperators++;
        }
        else if (getPriorityOfOperator(_expression[i]) > getPriorityOfOperator(operators.Top()))
        {
            operators.Push(_expression[i]);
            countOfOperators++;
        }
        else
        {
            while ((!operators.IsEmpty()) && (operators.Top() != '(')
                && (getPriorityOfOperator(_expression[i]) <= getPriorityOfOperator(operators.Top())))
            {
                string tmp;
                tmp.push_back(operators.Top());
                operators.Pop();
                operands.Push(tmp);
            }
            operators.Push(_expression[i]);
            countOfOperators++;
        }

        if (_expression[i] != ' ')
            lastSymbol = _expression[i];
    }

    if ((countOfOperands != countOfOperators + 1)
        || (countOfLeftBrackets != countOfRightBrackets)) throw exception("Неверное выражение");

    while (!operators.IsEmpty())
    {
        string tmp;
        tmp.push_back(operators.Top());
        operators.Pop();
        operands.Push(tmp);
    }

    Stack<string> reverseStackOfOperands(lengthOfExpression);
    for (; !operands.IsEmpty(); operands.Pop())
        reverseStackOfOperands.Push(operands.Top());

    int startPosition = 0;

    string postfixForm;
    while (!reverseStackOfOperands.IsEmpty())
    {
        startPosition = postfixForm.length();
        postfixForm.insert(startPosition, reverseStackOfOperands.Top());
        reverseStackOfOperands.Pop();
        buffer = ' ';
        postfixForm.insert(postfixForm.length(), buffer);
    }

    {
        PostfixForm::operands = new string[countOfOperands + 1];
        for (int i = 0; i < countOfOperands; i++)
            PostfixForm::operands[i] = _operands[i];
        PostfixForm::operands[countOfOperands] = " ";
        delete[] _operands;
    }
    
    return postfixForm;
}

double PostfixForm::Calculate(const string & _postfixForm, const Variables& _var)
{
    Stack<double> result(_postfixForm.size());//length
    string tmp;
    int value;

    for (int i = 0, j = 0; i <_postfixForm.size(); i++)//length
    {
        if ((_postfixForm[i] != ' ')&& (_postfixForm != "*") && 
            (_postfixForm != "/") && (_postfixForm != "+") && 
            (_postfixForm != "-"))
        {
            tmp.push_back(_postfixForm[i]);
        }
        else
        {
            /*if ((tmp != "*") && (tmp != "/") && (tmp != "+") && (tmp != "-"))
            {
                int idx = 0;
                while ((idx < _var.countOfVariables) && (_var.variables[idx++] != tmp));//
                idx--;
                result.Push(_var.values[idx]);
            }
            */
            if (tmp.size() != 0)
            {
                result.Push(_var[tmp]);
                tmp.clear();
            }
            else if (tmp == "*")
            {
                double b = result.Top(); result.Pop();
                double a = result.Top(); result.Pop();
                result.Push(a * b);
            }
            else if (tmp == "/")
            {
                double b = result.Top(); result.Pop();
                double a = result.Top(); result.Pop();
                if (b == 0) throw exception("Деление на ноль");
                result.Push(a / b);
            }
            else if (tmp == "+")
            {
                double b = result.Top(); result.Pop();
                double a = result.Top(); result.Pop();
                result.Push(a + b);
            }
            else if (tmp == "-")
            {
                double b = result.Top(); result.Pop();
                double a = result.Top(); result.Pop();
                result.Push(a - b);
            }
        }
        tmp.clear();
    }
    //
    for (size_t i = 0; i < _var.countOfVariables; i++)
    {
        cout << _var.variables[i] << " = " << _var.values[i] << endl;
    }
    //
    return result.Top();
   
}

int PostfixForm::getPriorityOfOperator(const char _operator)
{
    if ((_operator == '*') || (_operator == '/')) return 3;
    if ((_operator == '+') || (_operator == '-')) return 2;
    if (_operator == ')') return 1;
    return 0;
}

void PostfixForm::Clear()
{
    delete[] operands;
}
