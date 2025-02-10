#include <iostream>
#include <cmath>
#include <vector>

// Funkcja obliczająca węzły Czebyszewa
std::vector<double> calculateChebyshevNodes(int n, double x_a, double x_b) {
    std::vector<double> nodes(n + 1);
    for (int i = 0; i <= n; ++i) {
        nodes[i] = 0.5 * ((x_b - x_a) * cos((2 * i + 1) * M_PI / (2 * n + 2)) + (x_a + x_b));
    }
    return nodes;
}

// Funkcja obliczająca równomiernie rozmieszczone węzły
std::vector<double> calculateUniformNodes(int n, double x_a, double x_b) {
    std::vector<double> nodes(n + 1);
    double delta_x = (x_b - x_a) / n;
    for (int i = 0; i <= n; ++i) {
        nodes[i] = x_a + i * delta_x;
    }
    return nodes;
}

int main() {
    // Przedziały i wartości n
    std::vector<int> n_values = {5, 10, 15};
    double x_a = -3;
    double x_b = 8;

    for (int n : n_values) {
        // Oblicz węzły Czebyszewa
        std::vector<double> chebyshevNodes = calculateChebyshevNodes(n, x_a, x_b);
        std::cout << "Węzły Czebyszewa dla n = " << n << ": ";
        for (double node : chebyshevNodes) {
            std::cout << node << " ";
        }
        std::cout << std::endl;

        // Oblicz równomiernie rozmieszczone węzły
        std::vector<double> uniformNodes = calculateUniformNodes(n, x_a, x_b);
        std::cout << "Równomiernie rozmieszczone węzły dla n = " << n << ": ";
        for (double node : uniformNodes) {
            std::cout << node << " ";
        }
        std::cout << std::endl << std::endl;
    }

    return 0;
}