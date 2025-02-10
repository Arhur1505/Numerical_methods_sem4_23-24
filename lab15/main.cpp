#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

const double k = 1.38e-23;  
const double u = 1.66e-27;  
const double T = 100;       
const double m = 40 * u;   
const double sigma = std::sqrt(k * T / m);

double uniform_random() {
    return static_cast<double>(rand()) / RAND_MAX;
}

double* generateMaxwellNumbers(int NL) {
    double* Vn = new double[NL];

    for (int i = 0; i < NL; ++i) {
        double x1 = uniform_random();
        double x2 = uniform_random();
        double x3 = uniform_random();
        double x4 = uniform_random();

        double V1 = sigma * std::sqrt(-2 * std::log(x1)) * std::cos(2 * M_PI * x2);
        double V2 = sigma * std::sqrt(-2 * std::log(x1)) * std::sin(2 * M_PI * x2);
        double V3 = sigma * std::sqrt(-2 * std::log(x3)) * std::cos(2 * M_PI * x4);

        Vn[i] = std::sqrt(V1 * V1 + V2 * V2 + V3 * V3);
    }

    return Vn;
}

void saveHistogram(double* Vn, int NL) {
    const int numBins = 30;
    double binWidth = 5 * sigma / numBins;
    int bins[numBins] = {0};

    for (int i = 0; i < NL; ++i) {
        int bin = static_cast<int>(Vn[i] / binWidth);
        if (bin < numBins) {
            bins[bin]++;
        }
    }

    std::ofstream file("histogram_" + std::to_string(NL) + ".txt");
    for (int i = 0; i < numBins; ++i) {
        double binCenter = (i + 0.5) * binWidth;
        double phi = bins[i] / (static_cast<double>(NL) * binWidth);
        file << binCenter << " " << phi << "\n";
    }
    file.close();
}


void calculateStatistics(double* Vn, int NL, double& Vsr, double& s_Vsr, double& Vsr_kw, double& s_Vsr_kw) {
    double sum_V = 0.0;
    double sum_V2 = 0.0;
    double sum_V4 = 0.0;

    for (int i = 0; i < NL; ++i) {
        sum_V += Vn[i];
        sum_V2 += Vn[i] * Vn[i];
        sum_V4 += Vn[i] * Vn[i] * Vn[i] * Vn[i];
    }

    Vsr = sum_V / NL;
    Vsr_kw = sum_V2 / NL;

    double mean_V2 = sum_V2 / NL;
    s_Vsr = std::sqrt((sum_V2 - NL * Vsr * Vsr) / (NL * (NL - 1)));
    s_Vsr_kw = std::sqrt((sum_V4 - NL * mean_V2 * mean_V2) / (NL * (NL - 1)));
}

int main() {
    srand(time(0));

    int L_values[] = {3, 4, 5, 6};

    std::ofstream resultsFile("results.txt");
    resultsFile << std::fixed << std::setprecision(6);

    for (int L : L_values) {
        int NL = static_cast<int>(std::pow(10, L));
        double* Vn = generateMaxwellNumbers(NL);

        saveHistogram(Vn, NL);

        double Vsr, s_Vsr, Vsr_kw, s_Vsr_kw;
        calculateStatistics(Vn, NL, Vsr, s_Vsr, Vsr_kw, s_Vsr_kw);

        double Vsr_exact = std::sqrt(8 * k * T / (M_PI * m));
        double Vsr_kw_exact = 3 * k * T / m;

        resultsFile << "NL: " << NL << "\n";
        resultsFile << "Vsr: " << Vsr << ", Vsr_exact: " << Vsr_exact << "\n";
        resultsFile << "s(Vsr): " << s_Vsr << "\n";
        resultsFile << "Vsr_kw: " << Vsr_kw << ", Vsr_kw_exact: " << Vsr_kw_exact << "\n";
        resultsFile << "s(Vsr_kw): " << s_Vsr_kw << "\n\n";

        delete[] Vn;
    }

    resultsFile.close();

    return 0;
}
