#include <string>
#include <iostream>
#include "PostfixForm.h"

string PostfixForm::postfixForm;
int PostfixForm::countOfOperands;
string *PostfixForm::operands;


string PostfixForm::ConvertToPostfixForm(const string & _expression)
{
    string *_operands = new string[_expression.length()];
    string buffer;
    int lengthOfExpression = _expression.length();
    int numberOfOperators = 0;
    int numberOfOperands = 0;
    countOfOperands = 0;
    int numberOfLeftBrackets = 0;
    int numberOfRightBrackets = 0;
    char lastSymbol = 0;
    postfixForm.clear();
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
                numberOfOperands++;
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
            if (numberOfOperands == (numberOfOperators + 1)) throw exception("Неверное выражение");
            buffer.push_back(_expression[i]);
            if (i == (lengthOfExpression - 1))
            {
                numberOfOperands++;
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
            numberOfLeftBrackets++;
            operators.Push(_expression[i]);
        }
        else if (_expression[i] == ')')
        {
            if ((lastSymbol == '+') || (lastSymbol == '-')
                || (lastSymbol == '*') || (lastSymbol == '/')
                || (lastSymbol == '('))
                throw exception("Неверное выражение");
            numberOfRightBrackets++;
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
            numberOfOperators++;
        }
        else if (getPriorityOfOperator(_expression[i]) > getPriorityOfOperator(operators.Top()))
        {
            operators.Push(_expression[i]);
            numberOfOperators++;
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
            numberOfOperators++;
        }

        if (_expression[i] != ' ')
            lastSymbol = _expression[i];
    }

    if ((numberOfOperands != numberOfOperators + 1)
        || (numberOfLeftBrackets != numberOfRightBrackets)) throw exception("Неверное выражение");

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
    while (!reverseStackOfOperands.IsEmpty())
    {
        startPosition = postfixForm.length();
        postfixForm.insert(startPosition, reverseStackOfOperands.Top());
        reverseStackOfOperands.Pop();
        buffer = ' ';
        postfixForm.insert(postfixForm.length(), buffer);
    }

    countOfOperands = numberOfOperands;
    {
        PostfixForm::operands = new string[countOfOperands++];
        for (int i = 0; i < countOfOperands; i++)
            PostfixForm::operands[i] = _operands[i];
        delete[] _operands;
    }

    return postfixForm;
}

double PostfixForm::Calculate(const string & _postfixForm, const Variables& _var)
{
    Stack<double> result(postfixForm.length());
    string tmp;
    int value;

    for (int i = 0, j = 0; i < postfixForm.length(); i++)
    {
        cout << endl << "Iteration: #" << i << endl;

        if (postfixForm[i] != ' ')           
        {

        }
        else
        {
            tmp.push_back(postfixForm[i - 1]);
            if ((tmp != "*") && (tmp != "/") && (tmp != "+") && (tmp != "-"))
            {
                if (!isNumber(tmp))
                {
                    int idx = 0;
                    while ((idx < countOfOperands) && (operands[idx++] != tmp));

                    result.Push(_var.values[idx]);
                }
                else
                {
                    result.Push(stod(tmp, 0));
                }
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
    PostfixForm::countOfOperands = 0;
    PostfixForm::postfixForm.clear();
    delete[] operands;
}

string*& PostfixForm::getOperands()
{
    return operands;
}

int PostfixForm::getCountOfOperands()
{
    return countOfOperands;
}

bool PostfixForm::isNumber(const string& _str)
{
    return ((!_str.empty()) && (_str.find_first_not_of("0123456789") == _str.npos));
}