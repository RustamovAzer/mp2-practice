#include <iostream>
#include "TMatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    unsigned size;

    cout << endl << "¬ведите размер матриц: ";
    cin >> size;

    TMatrix<double> tm1(size), tm2(size), tm3, tm4;
    TVector<double> tv(size);
    double tmp;

    cout << "¬ведите первую матрицу: " << endl;
    cin >> tm1;
    cout << "¬ведите вторую матрицу: " << endl;
    cin >> tm2;
    cout << "¬ведите третью матрицу (size = 7): " << endl;
    cin >> tm2;
    cout << "¬ведите четвертую матрицу (size = 7): " << endl;
    cin >> tm2;
    cout << "¬ведите число:" << endl;
    cin >> tmp;
    cout << "¬ведите вектор: " << endl;
    cin >> tv;

    cout << "(matrix1 == matrix2): " << (tm1 == tm2) << endl;
    cout << "(matrix1 != matrix2): " << (tm1 != tm2) << endl;
    cout << "(matrix1 == matrix3): " << (tm1 == tm3) << endl;

    cout << "matrix1 + value:" << endl;
    cout << (tm1 + tmp) << endl;
    cout << "matrix1 - value:" << endl;
    cout << (tm1 - tmp) << endl;
    cout << "matrix1 * value:" << endl;
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
        cout << "ќшибка: " << msg;
    }

    try
    {
        tm1[73];
    }
    catch (char* msg)
    {
        cout << "ќшибка: " << msg;
    }

    system("pause");

}