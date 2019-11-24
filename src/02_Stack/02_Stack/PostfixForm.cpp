#include <string>
#include <iostream>
#include "PostfixForm.h"

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
    int typeOfLastSymbol = -1;

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
                buffer.clear();
                if (typeOfLastSymbol == 0)
                    throw exception("Incorrect expression 1");
                typeOfLastSymbol = 0;
            }
        }

        if (_expression[i] == ' ');
        else if ((_expression[i] != '+') && (_expression[i] != '-')
            && (_expression[i] != '*') && (_expression[i] != '/')
            && (_expression[i] != '(') && (_expression[i] != ')'))
        {
            buffer.push_back(_expression[i]);
        }
        else if (_expression[i] == '(')
        {
            operators.Push(_expression[i]);
            if ((typeOfLastSymbol == 0) || (typeOfLastSymbol == 3))
                throw exception("Incorrect expression 2");
            typeOfLastSymbol = 2;
        }
        else if (_expression[i] == ')')
        {
            countOfRightBrackets++;
            if (countOfRightBrackets > countOfLeftBrackets)
                throw exception("Incorrect expression 3");
            while (operators.Top() != '(')
            {
                string tmp;
                tmp.push_back(operators.Top());
                operators.Pop();
                operands.Push(tmp);
            }
            operators.Pop();
            if (typeOfLastSymbol == 1)
                throw exception("Incorrect expression 4");
            typeOfLastSymbol = 3;
        }
        else if (operators.IsEmpty())
        {
            operators.Push(_expression[i]);
            countOfOperators++;
            if ((typeOfLastSymbol == 1) || (typeOfLastSymbol == 2))
                throw exception("Incorrect expression 5");
            typeOfLastSymbol = 1;
        }
        else if (getPriorityOfOperator(_expression[i]) > getPriorityOfOperator(operators.Top()))
        {
            operators.Push(_expression[i]);
            countOfOperators++;
            if ((typeOfLastSymbol == 1) || (typeOfLastSymbol == 2))
                throw exception("Incorrect expression 6");
            typeOfLastSymbol = 1;
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
            if ((typeOfLastSymbol == 1) || (typeOfLastSymbol == 2)) throw exception("Incorrect expression 7");
            typeOfLastSymbol = 1;
        }

    }

    //if ((countOfOperands != countOfOperators + 1)
       // || (countOfLeftBrackets != countOfRightBrackets)) throw exception("Incorrect expression 8");

    if (buffer.length() != 0)
    {
        operands.Push(buffer);
        buffer.clear();
        countOfOperands++;
        typeOfLastSymbol = 0;
    }

    while (!operators.IsEmpty())
    {
        string tmp;
        tmp.push_back(operators.Top());
        operators.Pop();
        operands.Push(tmp);
    }

    string expression;
    while (!operands.IsEmpty())
    {
        expression.insert(0, " ");
        expression.insert(0, operands.Top());
        operands.Pop();
    }
    return expression;
    
}

double PostfixForm::Calculate(const string & input, const Variables& variables)
{
    Stack<double> result(input.length());
    string buffer;

    for (unsigned i = 0; i < input.size(); i++)
    {

        if ((input[i] != ' ') && (input[i] != '+') && (input[i] != '-') && (input[i] != '*') && (input[i] != '/'))
        {
            buffer.push_back(input[i]);
        }
        else
        {
            if (buffer.size() != 0)
            {
                result.Push(variables[buffer]);
                buffer.clear();
            }
            if (input[i] == '+')
            {
                double b = result.Top();
                result.Pop();
                double a = result.Top();
                result.Pop();
                result.Push(a + b);
            }
            else if (input[i] == '-')
            {
                double b = result.Top();
                result.Pop();
                double a = result.Top();
                result.Pop();
                result.Push(a - b);
            }
            else if (input[i] == '*')
            {
                double b = result.Top();
                result.Pop();
                double a = result.Top();
                result.Pop();
                result.Push(a * b);
            }
            else if (input[i] == '/')
            {
                double b = result.Top();
                result.Pop();
                double a = result.Top();
                result.Pop();
                if (b == 0) throw exception("Divizion by zero");
                result.Push(a / b);
            }
        }
    }
    return result.Top();
}

Variables PostfixForm::GetVariables(const string& input)
{
    string buffer;
    Variables out;

    for (int i = 0; i < input.size(); i++)
    {
        if ((input[i] != '+') && (input[i] != '-') && (input[i] != '*') && (input[i] != '/') && (input[i] != ' '))
        {
            buffer.push_back(input[i]);
        }
        else if (out.Count(buffer) != 0)
        {
            buffer.clear();
        }
        else if (buffer.size() != 0)
        {
            bool isNumeric = true;
            for (int j = 0; j < buffer.size(); j++)
            {
                if ((buffer[j] < 48) || (buffer[j] > 57)) isNumeric = false;
            }
            if (isNumeric)
            {
                out.Push(buffer, stoi(buffer));
            }
            else
            {
                double inputVariable;
                cout << "Input " << buffer << " ";
                cin >> inputVariable;
                out.Push(buffer, inputVariable);
            }
            buffer.clear();
        }
    }

    return out;
}

int PostfixForm::getPriorityOfOperator(const char _operator)
{
    if ((_operator == '*') || (_operator == '/')) return 3;
    if ((_operator == '+') || (_operator == '-')) return 2;
    if (_operator == ')') return 1;
    return 0;
}
