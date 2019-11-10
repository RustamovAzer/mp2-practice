#include "PostfixForm.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    bool ended = false;

    do
    {
        cout << endl << "Введите выражение.";
        cout << endl << "Выражение: ";
        string buffer;
        getline(cin, buffer);

        try
        {
            cout << "Польская форма: " << PostfixForm::ConvertToPostfixForm(buffer) << endl;

            Variables var(PostfixForm::operands);

            cout << "Ответ: ";
            cout << PostfixForm::Calculate(PostfixForm::ConvertToPostfixForm(buffer), var);
            cout << endl << endl;
            PostfixForm::Clear();
        }
        catch (const exception& e)
        {
            cout << "Ошибка: " << e.what() << endl;
        }
        cout << "1 - Выйти из программы "<< endl;
        cout << "0 - Новое выражение" << endl;
        cin >> ended;
        cin.ignore();
    } while (!ended);

    return 0;
}