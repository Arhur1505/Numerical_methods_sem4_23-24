#include <iostream>
#include <fstream>
#include <cmath>
#include </usr/include/gsl/gsl_eigen.h>

const double L = 10;
const int n = 200;
const double N = 1;
const double delta_alpha = 2;
const double alpha_max = 100;

void create_matrix_A(gsl_matrix *A, double dx2)
{
    for (int i = 0; i < n; ++i)
    {
        gsl_matrix_set(A, i, i, 2.0 / dx2);
        if (i > 0)
            gsl_matrix_set(A, i, i - 1, -1.0 / dx2);
        if (i < n - 1)
            gsl_matrix_set(A, i, i + 1, -1.0 / dx2);
    }
}

void create_matrix_B(gsl_matrix *B, double alpha, double dx)
{
    for (int i = 0; i < n; ++i)
    {
        double x = -L / 2 + dx * (i + 1);
        double rho = 1 + 4 * alpha * x * x;
        gsl_matrix_set(B, i, i, rho / N);
    }
}

void save_eigen_vectors(gsl_matrix *evec, std::string filename)
{
    std::ofstream file(filename);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            file << gsl_matrix_get(evec, i, j) << (j < 5 ? " " : "\n");
        }
    }
}

int main()
{
    gsl_matrix *A = gsl_matrix_alloc(n, n);
    gsl_matrix *B = gsl_matrix_alloc(n, n);
    gsl_vector *eval = gsl_vector_alloc(n);
    gsl_matrix *evec = gsl_matrix_alloc(n, n);
    gsl_eigen_gensymmv_workspace *w = gsl_eigen_gensymmv_alloc(n);
    std::ofstream file("eigen_values_vs_alpha.csv");

    double dx = L / (n + 1);
    double dx2 = dx * dx;

    for (double alpha = 0; alpha <= alpha_max; alpha += delta_alpha)
    {
        gsl_matrix_set_zero(A);
        gsl_matrix_set_zero(B);
        create_matrix_A(A, dx2);
        create_matrix_B(B, alpha, dx);

        gsl_eigen_gensymmv(A, B, eval, evec, w);
        gsl_eigen_gensymmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_ASC);

        file << alpha;
        for (int i = 0; i < 6; ++i)
        {
            double lambda = gsl_vector_get(eval, i);
            file << " " << std::sqrt(lambda);
        }
        file << std::endl;

        if (alpha == 0 || alpha == 100)
        {
            save_eigen_vectors(evec, "eigen_vectors_alpha_" + std::to_string((int)alpha) + ".csv");
        }
    }

    file.close();
    
    gsl_matrix_free(A);
    gsl_matrix_free(B);
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    gsl_eigen_gensymmv_free(w);

    return 0;
}
