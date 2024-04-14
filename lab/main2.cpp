#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

// Definicja funkcji f(x)
double f(double x) {
    return pow(x, 4) - 7.899*pow(x, 3) + 23.281114*pow(x, 2) + 14.73866033 - 30.33468152*x;
}

// Implementacja niemodyfikowanej metody siecznych

int main() {
    // Początkowe przybliżenia i tolerancja
  double x0 = 1.8; //x_k-1
  double x1 = 2.0; //x_k
  double x2; //x_k+1     

  double epsilon = 1e-6;  //przyblizenie
  double blad; // blad obliczany dla kazdej iter
  
  //Stworzenie 3 plikow z tabelkami
  std::ofstream outFile1("miejsce_zerowe_1.csv");
  std::ofstream outFile2("miejsce_zerowe_2.csv");
  std::ofstream outFile3("miejsce_zerowe_3.csv");

  //Nadanie nazw kolumn dla plikow
  
  outFile2 << "Iteracja,x,blad,f(x)\n";
  
    
  int iteracja = 0; 

    do {
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0)); // Obliczenie nowego przybliżenia
        blad = std::abs(x2 - x1); // Obliczenie błędu
        x0 = x1; // Aktualizacja x0 i x1 dla następnej iteracji
        x1 = x2;
        iteracja++;

        outFile2 << iteracja << "," << x2 << "," << blad << "," << f(x2) << "\n";
        // Wypisanie informacji o iteracji
        std::cout << "Iteracja " << iteracja << ": x = " << x2 << ", blad = " << blad << ", f(x) = " << f(x2) << std::endl;

    } while (blad > epsilon); // Warunek zakończenia - osiągnięcie zadanej dokładności
    
    std::cout << "Znaleziony pierwiastek: " << x2 << std::endl;

    return 0;
}