#include <iostream>
#include <fstream>
#include <cmath>

#define MAX_N 9

double f(double x)
{
    return log(x * x * x + 3 * x * x + x + 0.1) * sin(18 * x);
}

double trapezoidalRule(double *y, double h, int N)
{
    double S = 0.0;
    for (int i = 0; i < N; ++i)
    {
        S += (y[i] + y[i + 1]) * h / 2.0;
    }
    return S;
}

double threeEighthRule(double *y, double h, int N)
{
    double S = 0.0;
    for (int i = 0; i < N; i += 3)
    {
        S += (y[i] + 3 * y[i + 1] + 3 * y[i + 2] + y[i + 3]) * 3.0 * h / 8.0;
    }
    return S;
}

void richardsonExtrapolation(double D[MAX_N][MAX_N], int maxN)
{
    for (int k = 1; k < maxN; ++k)
    {
        for (int n = k; n < maxN; ++n)
        {
            D[n][k] = (pow(4, k) * D[n][k - 1] - D[n - 1][k - 1]) / (pow(4, k) - 1);
        }
    }
}

void writeResultsToFile(const char *filename, double D[MAX_N][MAX_N], int maxN)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Cannot open file " << filename << " for writing.\n";
        return;
    }
    for (int i = 0; i < maxN; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            outFile << D[i][j] << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

int main()
{
    const int maxN = MAX_N;
    const double a = 0.0;
    const double b = 1.0;

    double D_trap[MAX_N][MAX_N] = {0.0};
    double D_38[MAX_N][MAX_N] = {0.0};

    for (int n = 0; n < maxN; ++n)
    {
        int N_trap = 2 * (1 << n);
        double h_trap = (b - a) / N_trap;
        double y_trap[N_trap + 1];
        for (int i = 0; i <= N_trap; ++i)
        {
            y_trap[i] = f(a + i * h_trap);
        }
        D_trap[n][0] = trapezoidalRule(y_trap, h_trap, N_trap);

        int N_38 = 3 * (1 << n);
        double h_38 = (b - a) / N_38;
        double y_38[N_38 + 1];
        for (int i = 0; i <= N_38; ++i)
        {
            y_38[i] = f(a + i * h_38);
        }
        D_38[n][0] = threeEighthRule(y_38, h_38, N_38);
    }

    richardsonExtrapolation(D_trap, maxN);
    richardsonExtrapolation(D_38, maxN);

    writeResultsToFile("results_trapezoidal.txt", D_trap, maxN);
    writeResultsToFile("results_threeEighth.txt", D_38, maxN);

    return 0;
}
