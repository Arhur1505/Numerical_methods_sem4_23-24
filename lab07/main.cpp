#include <iostream>
#include <cmath>
#include <fstream>

const int MAX_N = 20;

double y(double x)
{
    return x / (1 + x * x);
}

void generujWezlyRownomierne(double wezly[], double xa, double xb, int n)
{
    double dx = (xb - xa) / n;
    for (int i = 0; i <= n; ++i)
    {
        wezly[i] = xa + i * dx;
    }
}

void generujWezlyCzebyszewa(double wezly[], double xa, double xb, int n)
{
    for (int i = 0; i <= n; ++i)
    {
        wezly[i] = 0.5 * ((xb - xa) * cos(M_PI * (2.0 * i + 1.0) / (2.0 * n + 2.0)) + (xa + xb));
    }
}

double wielomianInterpolacyjnyLagrangea(double xWezly[], double yWezly[], double x, int n)
{
    double wynik = 0.0;
    for (int i = 0; i <= n; ++i)
    {
        double L = 1.0;
        for (int j = 0; j <= n; ++j)
        {
            if (i != j)
            {
                L *= (x - xWezly[j]) / (xWezly[i] - xWezly[j]);
            }
        }
        wynik += yWezly[i] * L;
    }
    return wynik;
}

int main()
{
    int n_values[3] = {5, 10, 15};
    double xa = -3, xb = 8;
    double wezlyRownomierne[MAX_N + 1], wezlyCzebyszewa[MAX_N + 1], yWartosci[MAX_N + 1];
    std::ofstream plik;

    for (int n : n_values)
    {
        generujWezlyRownomierne(wezlyRownomierne, xa, xb, n);
        for (int i = 0; i <= n; ++i)
        {
            yWartosci[i] = y(wezlyRownomierne[i]);
        }

        plik.open("interpolacja_n" + std::to_string(n) + "_row.txt");
        for (int i = 0; i < 200; ++i)
        {
            double x = xa + i * (xb - xa) / 199;
            double wynik = wielomianInterpolacyjnyLagrangea(wezlyRownomierne, yWartosci, x, n);
            plik << x << " " << wynik << std::endl;
        }
        plik.close();

        generujWezlyCzebyszewa(wezlyCzebyszewa, xa, xb, n);
        for (int i = 0; i <= n; ++i)
        {
            yWartosci[i] = y(wezlyCzebyszewa[i]);
        }

        plik.open("interpolacja_n" + std::to_string(n) + "_czeb.txt");
        for (int i = 0; i < 200; ++i)
        {
            double x = xa + i * (xb - xa) / 199;
            double wynik = wielomianInterpolacyjnyLagrangea(wezlyCzebyszewa, yWartosci, x, n);
            plik << x << " " << wynik << std::endl;
        }
        plik.close();
    }
}