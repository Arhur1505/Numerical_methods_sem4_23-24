#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <tuple>

using namespace std;

// Funkcja obliczeniowa f1
float f1(float x) {
    return log(pow(x, 5) + 3 * pow(x, 2) + x + 9);
}

// Funkcja obliczeniowa f2
float f2(float x) {
    return pow(x, 6);
}

// Pierwszy iloraz różnicowy
float F1(float x1, float x2, float (*f)(float)) {
    return (f(x2) - f(x1)) / (x2 - x1);
}

// Drugi iloraz różnicowy
float F2(float x1, float x2, float x3, float (*f)(float)) {
    float w1 = (f(x3) - f(x2)) / (x3 - x2);
    float w2 = (f(x2) - f(x1)) / (x2 - x1);
    return (w1 - w2) / (x3 - x1);
}

// Wyznaczanie przybliżonego położenia minimum
float x_m(float x1, float x2, float x3, float (*f)(float)) {
    return (x1 + x2) / 2.0 - F1(x1, x2, f) / (2.0 * F2(x1, x2, x3, f));
}

void simulate(string filename, float x_start, int iterations, float (*f)(float)) {
    float h = 0.01;
    float x1 = x_start;
    float x2 = x1 + h;
    float x3 = x2 + h;
    float tab[3];

    ofstream file;
    file.open(filename);

    for (int i = 0; i < iterations; i++) {
        float xm = x_m(x1, x2, x3, f);
        //file << x1 << " " << x2 << " " << x3 << " " << xm << " " << F1(x1, x2, f) << " " << F2(x1, x2, x3, f) << endl;
        file << F1(x1, x2, f) << " " << F2(x1, x2, x3, f) << endl;

        float w1 = abs(x1 - xm);
        float w2 = abs(x2 - xm);
        float w3 = abs(x3 - xm);

        if ((w1 >= w2) && (w1 >= w3))
            tie(tab[0], tab[1], tab[2]) = tie(x2, x3, xm);
        else if ((w2 >= w1) && (w2 >= w3))
            tie(tab[0], tab[1], tab[2]) = tie(x1, x3, xm);
        else
            tie(tab[0], tab[1], tab[2]) = tie(x1, x2, xm);

        sort(tab, tab + 3);

        x1 = tab[0];
        x2 = tab[1];
        x3 = tab[2];
    }

    file.close();
}

int main() {
    simulate("F1a.txt", -0.5, 10, f1); // Symulacja dla funkcji f1a
    simulate("F1b.txt", -0.9, 10, f1); // Symulacja dla funkcji f1b
    simulate("F2.txt", 1.5, 100, f2); // Symulacja dla funkcji f2

    return 0;
}