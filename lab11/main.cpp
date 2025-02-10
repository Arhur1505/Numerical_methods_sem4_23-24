#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

void generate_signal(double data[], int N, bool add_noise)
{
    double omega = 4 * M_PI / N;
    for (int i = 0; i < N; ++i)
    {
        data[2 * i] = sin(omega * i) + sin(2 * omega * i) + sin(3 * omega * i);
        data[2 * i + 1] = 0;
        if (add_noise)
        {
            data[2 * i] += 2.0 * ((double)rand() / RAND_MAX) - 1.0;
        }
    }
}

void threshold_filter(double data[], int N, double threshold_ratio)
{
    std::vector<double> magnitudes(N);
    for (int i = 0; i < N; ++i)
    {
        magnitudes[i] = sqrt(data[2 * i] * data[2 * i] + data[2 * i + 1] * data[2 * i + 1]);
    }

    double max_magnitude = *std::max_element(magnitudes.begin(), magnitudes.end());
    double threshold = max_magnitude * threshold_ratio;

    for (int i = 0; i < N; ++i)
    {
        if (magnitudes[i] < threshold)
        {
            data[2 * i] = 0;
            data[2 * i + 1] = 0;
        }
    }
}

void save_to_file(const char *filename, double data[], int N)
{
    std::ofstream file(filename);
    for (int i = 0; i < N; ++i)
    {
        file << data[2 * i] << std::endl;
    }
    file.close();
}

int main()
{
    int k_values[] = {8, 10, 12};
    const int num_k = sizeof(k_values) / sizeof(k_values[0]);

    for (int i = 0; i < num_k; ++i)
    {
        int k = k_values[i];
        int N = 1 << k;
        double *data = new double[2 * N];

        generate_signal(data, N, true);

        gsl_fft_complex_radix2_forward(data, 1, N);
        threshold_filter(data, N, 0.5);
        gsl_fft_complex_radix2_backward(data, 1, N);
        for (int j = 0; j < N; ++j)
        {
            data[2 * j] /= N;
        }

        generate_signal(data, N, false);
        gsl_fft_complex_radix2_forward(data, 1, N);
        threshold_filter(data, N, 0.5);
        gsl_fft_complex_radix2_backward(data, 1, N);
    }

    return 0;
}