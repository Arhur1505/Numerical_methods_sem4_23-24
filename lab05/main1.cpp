#include <iostream>
#include <cmath>
#include <fstream>

double f(double x)
{
    return pow(x, 4) - 7.899 * pow(x, 3) + 23.281114 * pow(x, 2) + 14.73866033 - 30.33468152 * x;
}

double df(double x)
{
    return 4 * pow(x, 3) - 3 * 7.899 * pow(x, 2) + 2 * 23.281114 * x - 30.33468152;
}


double df_difference_quotient(double x, double delta)
{
    return (f(x + delta) - f(x - delta)) / (2 * delta);
}

void secant_method(double x0, double x1, double tol = 1e-6)
{
    std::ofstream file("secant_method_results.txt");
    double x2, error;
    int iteration = 0;

    do
    {
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        error = fabs(x2 - x1);
        x0 = x1;secant_method(1.5, 2.4);
        x1 = x2;

        file << "Iteracja " << iteration << ": x = " << x2 << ", f(x) = " << f(x2) << ", epsilon = " << error << std::endl;
        iteration++;
    } while (error > tol);

    file.close();
    std::cout << "Ostateczny wynik (niemodyfikowana metoda siecznych): x = " << x2 << std::endl;
}

void modified_secant_method(double x0, double x1, double delta, double tol = 1e-6)
{
    std::string fileName = "modified_secant_method_results_delta_" + std::to_string(delta) + ".txt";
    std::ofstream file(fileName.c_str()); // Otwarcie pliku do zapisu, uwzględniając wartość delta w nazwie pliku

    double x2, error;
    int iteration = 0;

    do
    {
        double derivative = df_difference_quotient(x1, delta);
        x2 = x1 - f(x1) / derivative;
        error = fabs(x2 - x1);
        x1 = x2;

        file << "Iteracja " << iteration << ": x = " << x2 << ", f(x) = " << f(x2) << ", epsilon = " << error << ", f'(x) = " << derivative << std::endl;
        iteration++;
    } while (error > tol);

    file.close();
    std::cout << "Ostateczny wynik (modyfikowana metoda siecznych, delta = " << delta << "): x = " << x2 << std::endl;
}

int main()
{
    // Przykładowe wywołanie metody siecznych
    std::cout << "Niemodyfikowana metoda siecznych:" << std::endl;
    secant_method(1.5, 2.4); // Ta funkcja również powinna zapisywać wyniki do pliku

    // Wywołanie modyfikowanej metody siecznych z różnymi wartościami delta
    std::cout << "\nModyfikowana metoda siecznych (delta = 0.1):" << std::endl;
    modified_secant_method(1.5, 2.4, 0.1);

    std::cout << "\nModyfikowana metoda siecznych (delta = 0.001):" << std::endl;
    modified_secant_method(1.5, 2.4, 0.001);

    return 0;
}