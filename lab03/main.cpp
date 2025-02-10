#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

void zapiszDoCSV(const float tabX[], int n, const std::string& nazwaPliku) {
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open()) {
        std::cout << "Nie można otworzyć pliku do zapisu." << std::endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        plik << tabX[i] << ", " << 0.02 * i << "\n";
    }

    plik.close();
}

int main(){
    int n = 1000;
    float h = 0.02;
    float beta = 0.0;
    float F0 = 0.0;
    float omega = 0.8;
    float tabB[n];

    float a1 = 1;
    float a2 = h * h - 2 - beta * h;
    float a3 = 1 + beta * h;

    tabB[0] = 1;
    tabB[1] = 0;
    for(int i = 2; i < n; i++){
        tabB[i] = F0*sin(omega*h*i)*h*h;
    }

    float tabD0[n];
    float tabD1[n];
    float tabD2[n];

    tabD0[0] = 1;
    tabD0[1] = 1;
    tabD1[0] = 0;
    tabD1[1] = -1;
    tabD2[0] = 0;
    tabD2[1] = 0;

    for(int i = 2; i < n; i++){
        tabD0[i] = a3;
        tabD1[i] = a2;
        tabD2[i] = a1;
    }

    float tabX[n];
    float x1 = 1;
    float x2 = 1;
    tabX[0] = (1 / tabD0[0])*(tabB[0] - tabD1[0] * x1 - tabD2[0] * x2);
    tabX[1] = (1 / tabD0[1])*(tabB[1] - tabD1[1] * tabX[0] - tabD2[1] * x2);

    for(int i = 2; i < n; i++){
        tabX[i] = (tabB[i] - tabD1[i] * tabX[i - 1] - tabD2[i] * tabX[i - 2])/tabD0[i];
    }

    std::string nazwapliku = "example";
    zapiszDoCSV(tabX, n, nazwapliku);

    // Poniżej dodano kod do utworzenia pliku z danymi i wywołania GNU Plot
    std::ofstream gnuplotScript("plot_script.gnu");
    if (!gnuplotScript.is_open()) {
        std::cout << "Nie można otworzyć pliku skryptu GNU Plot." << std::endl;
        return 1;
    }

    // Skrypt GNU Plot z zakresem osi y od -1 do 2
    gnuplotScript << "set term png\n";
    gnuplotScript << "set output 'plot.png'\n";
    gnuplotScript << "set yrange [-1:1]\n";  // Określenie zakresu osi y
    gnuplotScript << "plot 'example' with lines\n";
    gnuplotScript.close();

    // Wywołanie GNU Plot
    system("gnuplot plot_script.gnu");
}