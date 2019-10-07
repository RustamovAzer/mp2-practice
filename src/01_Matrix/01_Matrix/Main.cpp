#include <iostream>
#include "TMatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    unsigned size;

    cout << endl << "Введите размер матриц: ";
    cin >> size;

    TMatrix<double> tm1(size), tm2(size), tm3(3), tm4(3);
    TVector<double> tv(size);
    double tmp;

    cout << "Введите первую матрицу: " << endl;
    cin >> tm1;
    cout << "Введите вторую матрицу: " << endl;
    cin >> tm2;
    cout << "Введите третью матрицу (size = 3): " << endl;
    cin >> tm3;
    cout << "Введите четвертую матрицу (size = 3): " << endl;
    cin >> tm4;
    cout << "Введите число:" << endl;
    cin >> tmp;
    cout << "Введите вектор: " << endl;
    cin >> tv;

    cout << "(matrix1 == matrix2): " << (tm1 == tm2) << endl;
    cout << "(matrix1 != matrix2): " << (tm1 != tm2) << endl;
    cout << "(matrix1 == matrix3): " << (tm1 == tm3) << endl;

    cout << "matrix1 + число:" << endl;
    cout << (tm1 + tmp) << endl;
    cout << "matrix1 - число:" << endl;
    cout << (tm1 - tmp) << endl;
    cout << "matrix1 * число:" << endl;
    cout << (tm1 * tmp) << endl;

    cout << "matrix1 + matrix2:" << endl;
    cout << tm1 + tm2 << endl;
    cout << "matrix1 - matrix2:" << endl;
    cout << tm1 - tm2 << endl;
    cout << "matrix1 * matrix2:" << endl;
    cout << tm1 * tm2 << endl;

    cout << "matrix1 * vector:" << endl;
    cout << tm1 * tmp << endl;

    cout << "matrix3 = matrix1:" << endl;
    cout << (tm3 = tm1) << endl;

    cout << "Determinant(matrix1): " << endl;
    cout << tm1.Determinant() << endl;
    try
    {
        tm1 * tm4;
    }
    catch (char* msg)
    {
        cout << "Ошибка: " << msg << endl;
    }

    try
    {
        tm1[73];
    }
    catch (char* msg)
    {
        cout << "Ошибка: " << msg << endl;
    }

    system("pause");

}