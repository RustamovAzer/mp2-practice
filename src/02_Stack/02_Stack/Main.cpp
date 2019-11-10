#include "PostfixForm.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    bool ended = false;

    do
    {
        cout << endl << "������� ���������.";
        cout << endl << "���������: ";
        string buffer;
        getline(cin, buffer);

        try
        {
            cout << "�������� �����: " << PostfixForm::ConvertToPostfixForm(buffer) << endl;

            Variables var(PostfixForm::operands);

            cout << "�����: ";
            cout << PostfixForm::Calculate(PostfixForm::ConvertToPostfixForm(buffer), var);
            cout << endl << endl;
            PostfixForm::Clear();
        }
        catch (const exception& e)
        {
            cout << "������: " << e.what() << endl;
        }
        cout << "1 - ����� �� ��������� "<< endl;
        cout << "0 - ����� ���������" << endl;
        cin >> ended;
        cin.ignore();
    } while (!ended);

    return 0;
}