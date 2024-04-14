#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

float a = 1;
float b = -7.899;
float c = 23.281114;
float e = 14.73866033;
float d = -30.3346152;

double f(double x){
    return pow(x, 4)*a + pow(x, 3)*b + pow(x, 2)*c + d*x + e;
}

// Funkcja obliczająca iloraz różnicowy jako aproksymację pochodnej funkcji f
double df(double x, double delta_x){
    return (f(x + delta_x) - f(x - delta_x)) / (2 * delta_x);
}

void modified_secant_method(double x0, double delta_x, int z)
{
    double tol = 1e-6;
    std::ofstream file("modified" + std::to_string(z) + ".txt");
    double x1, x2, error, dfx0;
    int i = 0;

    do{ 
        dfx0 = df(x0, delta_x);
        x1 = x0 - f(x0) / dfx0;
        x2 = x1 - f(x1) / dfx0;  // Uwaga: używamy tego samego dfx0 dla obu przybliżeń
        error = fabs(x2 - x1);
        x0 = x2;
        file << "i = " << i << ": x = " << x2 << ", f(x) = " << f(x2) << ", eps = " << error << ", df(x) = " << dfx0 << std::endl;
        i++;
    } while (error > tol);
    file.close();
    std::cout << "Wynik: x " << z << " = " << x2 << std::endl;     
}

int main(){
    // Załóżmy, że znaleźliśmy pierwiastek wielokrotny w okolicy 1.5 i chcemy zastosować zmodyfikowaną metodę siecznych
    modified_secant_method(1.5, 0.1, 1);
    modified_secant_method(1.5, 0.001, 2);

    return 0;
}
