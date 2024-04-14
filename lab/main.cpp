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

int main(){
    s_method(1.5, 1.7, 1);
    s_method(1.8, 2.0, 2);
    s_method(2.1, 2.3, 3);

    return 0;
}