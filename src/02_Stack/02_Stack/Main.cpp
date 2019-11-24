#include "PostfixForm.h"

int main()
{
    bool ended = false;
    do
    {
        cout << endl << "Enter the expression.";
        cout << endl << "Expression: ";
        string input, rpn;
        getline(cin, input);
        Variables var(input.length());
        try
        {
            rpn = PostfixForm::ConvertToPostfixForm(input);
            cout << "Your expression in rpn form:" << endl << rpn << endl;
            var = PostfixForm::GetVariables(rpn);
            cout << "Result: " << PostfixForm::Calculate(rpn, var) << endl;
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << endl;
        }
        cout << "1 - Exit "<< endl;
        cout << "0 - New expression" << endl;
        cin >> ended;
        cin.ignore();
    } while (!ended);

    return 0;
}