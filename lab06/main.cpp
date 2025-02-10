#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

float a = 1;
float b = -7.899;
float c = 23.281114;
float e = 14.73866033;
float d = -30.33468152;
int i = 0;

double f(double x){
    return pow(x, 4)*a + pow(x, 3)*b + pow(x, 2)*c + e + d*x;
}

double diff(double x, double delta){
    return f(x)/(f(x + delta) - f(x - delta)) / (2 * delta);
}

double df(double x){
    return 4 * pow(x, 3) - 3 * 7.899 * pow(x, 2) + 2 * 23.281114 * x - 30.33468152;
}

double u(double x){
    return f(x) / df(x);
}

void s_method(double x0, double x1, int z)
{   
    std::ofstream file("zwy" + std::to_string(z) + ".txt");
    double tol = 1e-6;
    double x2, error;
    i = 0;

    do{ 
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        error = fabs(x2 - x1);
        x0 = x1;
        x1 = x2;
        file << "i = " << i << ": x = " << x2 << ", f(x) = " << f(x2) << ", eps = " << error << ", f'(x) = " << df(x2) << std::endl;
        i++;
    } while (error > tol);

    file.close();
    std::cout << "Wynik: x" << z << " = " << x2 << std::endl;     
}

void m_s_method(double x0, double x1, int z)
{   
    std::ofstream file("mod" + std::to_string(z) + ".txt");
    double tol = 1e-6;
    double x2, error;
    i = 0;

    do
    {
        x2 = x1 - u(x1) * (x1 - x0) / (u(x1) - u(x0));
        error = std::abs(x2 - x1);
        x0 = x1;
        x1 = x2;
        
        file << "i = " << i << ": x = " << x2 << ", f(x) = " << f(x2) << ", eps = " << error << ", f'(x) = " << df(x2) << std::endl;
        i++;
    } while (error > tol);

    file.close();
    std::cout << "Wynik modyfikowana: x" << z << " = " << x2 << std::endl;
}

void m_s_method_d(double x0, double x1, double delta, int z)
{   
    std::ofstream file("mod" + std::to_string(z) + "d.txt");
    double tol = 1e-6;
    double x2, error;
    i = 0;

    do
    {
        x2 = x1 - diff(x1, delta) * (x1 - x0) / (diff(x1, delta) - diff(x0, delta));
        error = std::abs(x2 - x1);
        x0 = x1;
        x1 = x2;
        
        file << "i = " << i << ": x = " << x2 << ", f(x) = " << f(x2) << ", eps = " << error << ", f'(x) = " << df(x2) << std::endl;
        i++;
    } while (error > tol);

    file.close();
    std::cout << "Wynik modyfikowana, delta = " << delta << ": x" << z << " = " << x2 << std::endl;
}

int main(){
    s_method(1.6, 1.7, 1);
    s_method(1.8, 1.9, 2);
    s_method(2.2, 2.3, 3);

    m_s_method(1.6, 1.7, 1);
    m_s_method(1.8, 1.9, 2);
    m_s_method(2.2, 2.3, 3);

    m_s_method_d(2.2, 2.3, 0.1, 4);
    m_s_method_d(2.2, 2.3, 0.001, 5);

    return 0;
}