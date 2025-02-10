#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <numeric>
#include <fstream>

using namespace std;

#define EPS 3.0e-11

float gammln(float xx)
{
    double x, y, tmp, ser;
    static double cof[6] = {76.18009172947146, -86.50532032941677,
                            24.01409824083091, -1.231739572450155,
                            0.1208650973866179e-2, -0.5395239384953e-5};
    int j;

    y = x = xx;
    tmp = x + 5.5;
    tmp -= (x + 0.5) * log(tmp);
    ser = 1.000000000190015;
    for (j = 0; j <= 5; j++)
        ser += cof[j] / ++y;
    return -tmp + log(2.5066282746310005 * ser / x);
}

void gauleg(float x1, float x2, float x[], float w[], int n)
{
    int m, j, i;
    double z1, z, xm, xl, pp, p3, p2, p1;

    m = (n + 1) / 2;
    xm = 0.5 * (x2 + x1);
    xl = 0.5 * (x2 - x1);
    for (i = 1; i <= m; i++)
    {
        z = cos(3.141592654 * (i - 0.25) / (n + 0.5));
        do
        {
            p1 = 1.0;
            p2 = 0.0;
            for (j = 1; j <= n; j++)
            {
                p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3) / j;
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);
            z1 = z;
            z = z1 - p1 / pp;
        } while (fabs(z - z1) > EPS);
        x[i] = xm - xl * z;
        x[n + 1 - i] = xm + xl * z;
        w[i] = 2.0 * xl / ((1.0 - z * z) * pp * pp);
        w[n + 1 - i] = w[i];
    }
}
#undef EPS

#define EPS 3.0e-14
#define MAXIT 10

void gaulag(float x[], float w[], int n, float alf)
{
    float gammln(float xx);
    int i, its, j;
    float ai;
    double p1, p2, p3, pp, z, z1;

    for (i = 1; i <= n; i++)
    {
        if (i == 1)
        {
            z = (1.0 + alf) * (3.0 + 0.92 * alf) / (1.0 + 2.4 * n + 1.8 * alf);
        }
        else if (i == 2)
        {
            z += (15.0 + 6.25 * alf) / (1.0 + 0.9 * alf + 2.5 * n);
        }
        else
        {
            ai = i - 2;
            z += ((1.0 + 2.55 * ai) / (1.9 * ai) + 1.26 * ai * alf /
                                                       (1.0 + 3.5 * ai)) *
                 (z - x[i - 2]) / (1.0 + 0.3 * alf);
        }
        for (its = 1; its <= MAXIT; its++)
        {
            p1 = 1.0;
            p2 = 0.0;
            for (j = 1; j <= n; j++)
            {
                p3 = p2;
                p2 = p1;
                p1 = ((2 * j - 1 + alf - z) * p2 - (j - 1 + alf) * p3) / j;
            }
            pp = (n * p1 - (n + alf) * p2) / z;
            z1 = z;
            z = z1 - p1 / pp;
            if (fabs(z - z1) <= EPS)
                break;
        }
        x[i] = z;
        w[i] = -exp(gammln(alf + n) - gammln((float)n)) / (pp * n * p2);
    }
}
#undef EPS
#undef MAXIT

#define EPS 3.0e-14
#define PIM4 0.7511255444649425
#define MAXIT 10

void gauher(float x[], float w[], int n)
{
    int i, its, j, m;
    double p1, p2, p3, pp, z, z1;

    m = (n + 1) / 2;
    for (i = 1; i <= m; i++)
    {
        if (i == 1)
        {
            z = sqrt((double)(2 * n + 1)) - 1.85575 * pow((double)(2 * n + 1), -0.16667);
        }
        else if (i == 2)
        {
            z -= 1.14 * pow((double)n, 0.426) / z;
        }
        else if (i == 3)
        {
            z = 1.86 * z - 0.86 * x[1];
        }
        else if (i == 4)
        {
            z = 1.91 * z - 0.91 * x[2];
        }
        else
        {
            z = 2.0 * z - x[i - 2];
        }
        for (its = 1; its <= MAXIT; its++)
        {
            p1 = PIM4;
            p2 = 0.0;
            for (j = 1; j <= n; j++)
            {
                p3 = p2;
                p2 = p1;
                p1 = z * sqrt(2.0 / j) * p2 - sqrt(((double)(j - 1)) / j) * p3;
            }
            pp = sqrt((double)2 * n) * p2;
            z1 = z;
            z = z1 - p1 / pp;
            if (fabs(z - z1) <= EPS)
                break;
        }
        x[i] = z;
        x[n + 1 - i] = -z;
        w[i] = 2.0 / (pp * pp);
        w[n + 1 - i] = w[i];
    }
}
#undef EPS
#undef PIM4
#undef MAXIT

float f1(float x)
{
    return x / (4 * x * x + 1);
}

float f2a(float x)
{
    return pow(x, 5);
}

float f2b(float x)
{
    return pow(x, 10);
}

float f3a(float x)
{
    return pow(sin(x), 2);
}

float f3b(float y)
{
    return pow(sin(y), 4);
}

float factorial(int k)
{
    float result = 1.0;
    for (int i = 1; i <= k; i++)
    {
        result *= i;
    }
    return result;
}

int main()
{
    float a = 0;
    float b = 2;
    float x[21];
    float w[21];
    float wx, wy, wynik;
    vector<float> errors1, errors2_k5, errors2_k10, errors3;

    ofstream file1("errors1.txt");
    ofstream file1_sum("sum_w_Gauss_Legendre.txt");

    cout << "Całka pierwsza:" << endl;
    for (int n = 2; n <= 20; n++)
    {
        float sum_w = 0;
        gauleg(a, b, x, w, n);
        wx = 0;
        for (int i = 1; i <= n; i++)
        {
            wx += w[i] * f1(x[i]);
            sum_w += w[i];
        }
        file1_sum << n << " " << sum_w << endl; // Zapis do pliku
        float c1a = 0.5 / 4.0 * log(abs(4.0 * b * b + 1.0) / (4.0 * a * a + 1.0));
        float error = abs(wx - c1a);
        errors1.push_back(error);
        file1 << error << " " << endl;
        cout << wx << " ";
    }
    cout << endl;
    file1.close();
    file1_sum.close();

    ofstream file2_k5("errors2_k5.txt");
    ofstream file2_k5_sum("sum_w_Gauss_Laguerre_k5.txt");
    cout << "Całka druga dla k=5:" << endl;
    for (int n = 2; n <= 20; n++)
    {
        gaulag(x, w, n, 0);
        wx = 0;
        float sum_w = 0;
        for (int i = 1; i <= n; i++)
        {
            wx += w[i] * f2a(x[i]);
            sum_w += w[i];
        }
        file2_k5_sum << n << " " << sum_w << endl; // Zapis do pliku
        float c2a = factorial(5);
        float error = abs(wx - c2a);
        errors2_k5.push_back(error);
        file2_k5 << error << " " << endl;
        cout << wx << " ";
    }
    cout << endl;
    file2_k5.close();
    file2_k5_sum.close();

    ofstream file2_k10("errors2_k10.txt");
    ofstream file2_k10_sum("sum_w_Gauss_Laguerre_k10.txt");
    cout << "Całka druga dla k=10:" << endl;
    for (int n = 2; n <= 20; n++)
    {
        gaulag(x, w, n, 0);
        wx = 0;
        float sum_w = 0;
        for (int i = 1; i <= n; i++)
        {
            wx += w[i] * f2b(x[i]);
            sum_w += w[i];
        }
        file2_k10_sum << n << " " << sum_w << endl; // Zapis do pliku
        float c2a = factorial(10);
        float error = abs(wx - c2a);
        errors2_k10.push_back(error);
        file2_k10 << error << " " << endl;
        cout << wx << " ";
    }
    cout << endl;
    file2_k10.close();
    file2_k10_sum.close();

    ofstream file3("errors3.txt");
    cout << "Całka trzecia:" << endl;
    for (int n = 2; n <= 15; n++)
    {
        gauher(x, w, n);
        wx = 0;
        wy = 0;
        for (int i = 1; i <= n; i++)
        {
            wx += w[i] * f3a(x[i]);
            wy += w[i] * f3b(x[i]);
        }

        wynik = wx * wy;
        float cdok = 0.1919832644;
        float error = abs(wynik - cdok);
        errors3.push_back(error);
        file3 << error << " " << endl;
        cout << wynik << " ";
    }
    cout << endl;
    file3.close();

    return 0;
}