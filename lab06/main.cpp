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
    return pow(x, 4)*a + pow(x, 3)*b + pow(x, 2)*c + e + d*x;
}


double df_difference(double x, double delta){
    return (f(x + delta) - f(x - delta)) / (2 * delta);
}


double df(double x){
    return 4 * pow(x, 3) - 3 * 7.899 * pow(x, 2) + 2 * 23.281114 * x - 30.33468152;
}


void s_method(double x0, double x1, int z)
{   
    double tol = 1e-6;
    std::ofstream file("zwyk" + std::to_string(z) + ".txt");
    double x2, error;
    int i = 0;

    do{ 
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        error = fabs(x2 - x1);
        x0 = x1;
        x1 = x2;
        file << "i = " << i << ": x = " << x2 << ", f(x) = " << f(x2) << ", eps = " << error << std::endl;
        i++;
    } while (error > tol);
    file.close();
    std::cout << "Wynik: x " << z << " = " << x2 << std::endl;     
}


void m_s_method(double x0, double x1, double delta, int z)
{   
    double tol = 1e-6;
    std::string fileName = "mod" + std::to_string(z) + "_" + std::to_string(delta) + ".txt";
    std::ofstream file(fileName.c_str()); // Otwarcie pliku do zapisu, uwzględniając wartość delta w nazwie pliku

    double x2, error;
    int iteration = 0;

    do
    {
        double derivative = df_difference(x1, delta);
        x2 = x1 - f(x1) / derivative;
        error = fabs(x2 - x1);
        x1 = x2;

        file << "i = " << iteration << ": x = " << x2 << ", f(x) = " << f(x2) << ", eps = " << error << ", f'(x) = " << derivative << std::endl;
        iteration++;
    } while (error > tol);

    file.close();
    std::cout << "Wnik modyfikowana, delta = " << delta << ": x" << z << "= " << x2 << std::endl;
}

int main(){
    s_method(1.5, 1.7, 1);
    s_method(1.8, 2.0, 2);
    s_method(2.0, 2.4, 3);

    m_s_method(1.5, 1.7, 0.1, 1);
    m_s_method(1.8, 2.0, 0.1, 2);
    m_s_method(2.0, 2.4, 0.1, 3);

    m_s_method(1.5, 1.7, 0.001, 1);
    m_s_method(1.8, 2.0, 0.001, 2);
    m_s_method(2.0, 2.4, 0.001, 3);

    return 0;
}