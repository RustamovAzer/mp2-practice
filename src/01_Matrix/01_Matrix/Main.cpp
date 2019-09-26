#include <iostream>
#include "TMatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    TVector<double> vectorA(3), vectorB(2), vectorC(1), vectorRez(3);
    TMatrix<double> matrixA(3), matrixB(3), matrixC(2), matrixRez(3);
    TVector <TVector<double>> VVectorA(3), VVectorB(2);

    for (int i = 0; i < 3; i++)
    {
        TVector<double> temp(3 - i);
        for (int j = i; j < 3; j++)
            temp[j - i] = (double)(i + j + 1);
        VVectorA[i] = temp;
    }

    vectorA.GenerateVector();
    matrixA.Generate();
    matrixB.Generate();
    matrixC.Generate();
    matrixRez.Generate();


    cout << "Matrix = Vector<Vector>A(3): " << endl;
    try
    {
        matrixRez = VVectorA;
        cout << matrixRez;

    }
    catch (char* msg)
    {
        cout << "Ошибка:" <<msg<<endl;
    }

    cout << "Matrix = Vector<Vector>B(2): ";
    try
    {
        matrixRez = VVectorB;
        cout << matrixRez;

    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "D = B:" << endl;
    matrixRez = matrixB;

    cout << "D" << endl << matrixRez << "B" << endl << matrixB;

    cout << "Проверка на (A == B): ";
    try
    {
        if (matrixA == matrixB)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Проверка на (D == B): ";
    try
    {
        if (matrixRez == matrixB)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Проверка на (A == C): ";
    try
    {
        if (matrixA == matrixC)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }


    cout << "Проверка на равенство матриц (A != B): ";
    try
    {
        if (matrixA != matrixB)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Проверка на равенство матриц (D != B): ";
    try
    {
        if (matrixRez != matrixB)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Проверка на равенство матриц (A != C): ";
    try
    {
        if (matrixA != matrixC)
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Сложение матриц (A + B):" << endl;
    try
    {
        matrixRez = matrixA + matrixB;
        cout << matrixRez;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Сложение матриц (A + C): ";
    try
    {
        matrixRez = matrixA + matrixC;
        cout << matrixRez;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Разность матриц (A - B): " << endl;
    try
    {
        matrixRez = matrixA - matrixB;
        cout << matrixRez;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Разность матриц (A - C): ";
    try
    {
        matrixRez = matrixA - matrixC;
        cout << matrixRez;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Умножение матриц (A * B): " << endl;
    try
    {
        matrixRez = matrixA * matrixB;
        cout << matrixRez;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Умножение матриц (A * C): ";
    try
    {
        matrixRez = matrixA * matrixC;
        cout << matrixRez;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "A + 5:" << endl;
    matrixRez = matrixA + 5;
    cout << matrixRez;

    cout << "A - 5:" << endl;
    matrixRez = matrixA - 5;
    cout << matrixRez;

    cout << "A * 5:" << endl;
    matrixRez = matrixA * 5;
    cout << matrixRez;

    cout << "Умножение матрицы на вектор (A * vectorB):" << endl;
    try
    {
        vectorRez = matrixA * vectorA;
        cout << vectorRez << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }
    cout << "Умножение матрицы на вектор (A * vectorB): ";
    try
    {
        vectorRez = matrixA * vectorB;
        cout << vectorRez << endl;
    }
    catch (char* msg)
    {
        cout << "Ошибка:" << msg << endl;
    }

    cout << "Детерминант матрицы A: " << matrixA.Determinant() << endl;

}