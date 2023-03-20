﻿#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Optimization
{
protected:
    float const a = 0.25f; // Нижняя граница отрезка неопределённости
    float const b = 2.0f; // Верхняя граница отрезка неопределённости

    /*

        Метод расчёта целевой функции, заданной в условии.

        Вариант 29.

    */
    float f(float x)
    {
        return x * x + 1.0f / x;
    }

    /*

        Метод расчёта производной целевой функции.

    */
    float f_(float x)
    {
        return 2 * x - 1 / (x * x);
    }

public:
    /*

        Метод основного алгоритма.

        Неопределён для последующего полиморфизма.

    */
    virtual void algorithm(int N) = 0;
};

class FibonacciNumberMethod : Optimization
{
protected:
    vector <int> fibonacci = { 0, 1 }; // Вектор числел Фибоначчи. Минимальное кол-во чисел - 2.

    /*

        Метод расчёта чисел Фибоначчи.

        Принимаемый на вход параметр N - кол-во чисел.
        N также включает в себя первые два числа {0, 1}.

    */
    void fibonacciCalculation(int N)
    {
        for (int i = 0; i < N - 2; i++)
        {
            fibonacci.push_back(fibonacci[i] + fibonacci[i + 1]);
        }
    }
public:
    void algorithm(int N) override
    {
        fibonacciCalculation(N);

        float E = (b - a) / (2.0f * fibonacci[N - 1]);
        float delta = E / 100.0f;
        float a_changeable = a, b_changeable = b;
        float x1, x2, _x, y1, y2, _y, E_calculated, E_guaranteed, _E1;

        int k = 2;

        x1 = a_changeable + (b_changeable - a_changeable) * fibonacci[N - 1 - 2] / fibonacci[N - 1];
        y1 = f(x1);

        x2 = a_changeable + (b_changeable - a_changeable) * fibonacci[N - 1 - 1] / fibonacci[N - 1];
        y2 = f(x2);

        E_calculated = (b_changeable - a_changeable) / (2 * fibonacci[N - 1]) + delta / 2;

        do
        {
            if (y1 < y2)
            {
                b_changeable = x2;
                x2 = x1;
                y2 = y1;
                x1 = a_changeable + b_changeable - x2;
                y1 = f(x1);
            }
            else
            {
                a_changeable = x1;
                x1 = x2;
                y1 = y2;
                y1 = y2;
                x2 = a_changeable + b_changeable - x1;
                y2 = f(x2);
            }

            k++;

        } while (k < N - 1);

        if (y1 < y2)
        {
            b_changeable = x2;
            x2 = x1;
            y2 = y1;
        }
        else
            a_changeable = x1;

        x1 = x2 - delta;
        y1 = f(x1);

        if (y1 < y2)
            b_changeable = x2;
        else
            a_changeable = x1;

        _x = (a_changeable + b_changeable) / 2;
        _y = f(_x);

        E_guaranteed = (b_changeable - a_changeable) / 2;
        _E1 = f_(_x);

        cout << "~x: " << _x << "   ~y: " << _y << "    Е-гарантированное: " << E_guaranteed << "   ~Е1: " << _E1 << "  Е-расчётное: " << E_calculated << "\n";
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Метод чисел Фибоначчи:\n\n";

    FibonacciNumberMethod* fibonacciNumberMethod = new FibonacciNumberMethod();

    for (int i = 1; i <= 5; i++)
        fibonacciNumberMethod->algorithm(i * 10);

    fibonacciNumberMethod->~FibonacciNumberMethod();

    delete fibonacciNumberMethod;
}