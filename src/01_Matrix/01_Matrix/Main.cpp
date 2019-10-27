#include <iostream>
#include "TMatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    unsigned msize, vsize;

    cout << endl << "Введите размер векторов: ";
    cin >> vsize;

    cout << endl << "Введите размер матриц: ";
    cin >> msize;

    TMatrix<double> tm1(msize), tm2(msize), tm3(msize+1);
    TVector<double> tv1(vsize), tv2(vsize);
    double tmp;

    cout << "Введите первую матрицу: " << endl;
    cin >> tm1;
    
    cout << "Введите вторую матрицу: " << endl;
    cin >> tm2;
    cout << "Введите третью матрицу(размер на 1 больше): " << endl;
    cin >> tm3;

    cout << "Введите первый вектор: " << endl;
    cin >> tv1;
    cout << "Введите первый вектор: " << endl;
    cin >> tv2;
    cout << "Введите число:" << endl;
    cin >> tmp;
    

    cout << "Выберите тест" << endl;
    cout << "1 : Сравнение векторов" << endl;
    cout << "2 : Вектор1 + число" << endl;
    cout << "3 : Вектор1 - число" << endl;
    cout << "4 : Вектор1 * число" << endl;
    cout << "5 : Вектор1 + вектор2" << endl;
    cout << "6 : Вектор1 - вектор2" << endl;
    cout << "7 : Вектор1 * вектор2" << endl;

    cout << "8 : Сравнение матриц" << endl;
    cout << "9 : Матрица1 + число" << endl;
    cout << "10: Матрица1 - число" << endl;
    cout << "11: Матрица1 * число" << endl;
    cout << "12: Матрица1 + матрица2" << endl;
    cout << "13: Матрица1 - матрица2" << endl;
    cout << "14: Матрица1 = матрица2(присваивание)" << endl;
    cout << "15: Матрица1 * матрица2" << endl;
    cout << "16: Детерминант матрицы1" << endl;
    cout << "0 : Выход " << endl;

    int test;

    do
    {
        cin >> test;
        switch (test)
        {
        case 1:
            cout << (tv1 == tv2) << endl;
            break;
        case 2:
            cout << (tv1 + tmp) << endl;
            break;
        case 3:
            cout << (tv1 - tmp) << endl;
            break;
        case 4:
            cout << (tv1 * tmp) << endl;
            break;
        case 5:
            cout << (tv1 + tv2) << endl;
            break;
        case 6:
            cout << (tv1 - tv2) << endl;
            break;
        case 7:
            cout << (tv1 * tv2) << endl;
            break;
        case 8:
            cout << (tm1 == tm2) << endl;
            break;
        case 9:
            cout << (tm1 + tmp) << endl;
            break;
        case 10:
            cout << (tm1 - tmp) << endl;
            break;
        case 11:
            cout << (tm1 * tmp) << endl;
            break;
        case 12:
            cout << (tm1 + tm2) << endl;
            break;
        case 13:
            cout << (tm1 - tm2) << endl;
            break;
        case 14:
            cout << (tm1 = tm2) << endl;
            break;
        case 15:
            cout << (tm1 * tm2) << endl;
            break;
        case 16:
            cout << tm1.Determinant() << endl;
            break;
        }
    } while (test != 0);
    

    cout << "Выберите тест исключений" << endl;
    cout << "1 : Умножение матриц разных размеров" << endl;
    cout << "2 : Сложение матриц разных размеров" << endl;
    cout << "3 : Вычитание матриц разных размеров" << endl;
    cout << "4 : Создание матрицы неположительного размера" << endl;
    cout << "5 : Выход индекса за пределы" << endl;
    cout << "0 : Выход " << endl;

    do
    {
        cin >> test;
        switch (test)
        {
        case 1:
            try
            {
                tm1 * tm3;
            }
            catch (exception e)
            {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 2:
            try
            {
                tm1 + tm3;
            }
            catch (exception e)
            {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                tm1 - tm3;
            }
            catch (exception e)
            {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 4:
            try
            {
                TMatrix<double> tm4(-2);
            }
            catch (exception e)
            {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        case 5:
            try
            {
                tm1[73];
            }
            catch (exception e)
            {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
    } while (test >= 1);

    system("pause");

}