#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

void save_fft_details(const char* filename, double data[], int N) {
    std::ofstream file(filename);
    for (int i = 0; i < N; ++i) {
        double real = data[2 * i];
        double imag = data[2 * i + 1];
        double magnitude = sqrt(real * real + imag * imag);
        file << real << "," << imag << "," << magnitude << std::endl;
    }
    file.close();
}

void generate_signal(double data[], int N, bool add_noise)
{
    double omega = 4 * M_PI / N;
    for (int i = 0; i < N; ++i)
    {
        data[2 * i] = sin(omega * i) + sin(2 * omega * i) + sin(3 * omega * i);
        data[2 * i + 1] = 0;
        if (add_noise)
        {
            data[2 * i] += 2.0 * ((double)rand() / RAND_MAX) - 1.0; // Dodawanie szumu
        }
    }
}

int main() {
    const int k = 8;
    int N = 1 << k;
    double *data = new double[2 * N];

    generate_signal(data, N, true);
    gsl_fft_complex_radix2_forward(data, 1, N);
    save_fft_details(("fft_details_k" + std::to_string(k) + ".txt").c_str(), data, N);

    delete[] data;
    return 0;
}
