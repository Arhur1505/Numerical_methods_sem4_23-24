#include<iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include <vector>
#include <functional>
#include <iomanip>

#include "/usr/include/gsl/gsl_math.h"
#include "/usr/include/gsl/gsl_linalg.h"
#include "/usr/include/gsl/gsl_eigen.h"

using namespace std;

double f1(double x) {
    return 1.0/(1.0 + x*x);
}

double f2(double x) {
    return cos(2*x);
}

double phi(double x, double xi_minus_2, double xi_minus_1, double xi, double xi_plus_1, double xi_plus_2, double h) {
    if( x>= xi_minus_2 && x < xi_minus_1 ) return 1/pow(h,3) * pow(x - xi_minus_2, 3);
    else if( x >= xi_minus_1 && x < xi )
        return 1/pow(h,3) * ( pow(h,3) + 3*pow(h,2)*(x - xi_minus_1) + 3*h* pow((x - xi_minus_1),2) - 3* pow((x - xi_minus_1),3) );
    else if( x >= xi && x < xi_plus_1)
        return 1/pow(h,3) * ( pow(h,3) + 3*pow(h,2)*(xi_plus_1 - x) + 3*h* pow((xi_plus_1 - x),2) - 3* pow((xi_plus_1 - x),3) );
    else if ( x >= xi_plus_1 && x < xi_plus_2)
        return 1/pow(h,3) * pow((xi_plus_2 - x) ,3);
    return  0.0;
}


double interpolate(double x, const std::vector<double>& c, const std::vector<double>& xx, double h) {
    double sum = 0.0;
    int n = c.size(); // N+1 - po spuszowaniu C_0 i C_n+1
    for (int i = 0; i < n ; ++i) {
        sum += c[i] * phi(x, xx[i], xx[i+1], xx[i+2], xx[i+3], xx[i+4], h);
    }
    return sum;
}


std::vector<double> convert_gsl_to_vector(gsl_vector* vector_gsl, int N){
    std::vector<double> vect(N);
    for (int i = 0; i < N; ++i) {
        vect[i] = gsl_vector_get(vector_gsl, i);
    }
    return vect;
}


double dfdx(std::function<double(double)>f, double x) {
    const double Delta_X = 0.01;
    return ( f(x+Delta_X) - f(x-Delta_X) ) / (2*Delta_X);
}

void saveNodesToFile(const vector<double>& x, const vector<double>& y, int num_nodes) {
    ofstream file("data/nodes_xi_" + to_string(num_nodes) + "f_2.txt");
    file << "x" << " " << "y\n";
    for (size_t i = 0; i < x.size(); ++i) {
        file << x[i] << " " << y[i] << endl;
    }
    file.close();
}



int main() {
    const int num_nodes[] = {6,7,14 };
    const double x_min = -5.0; const double x_max = 5.0;

    double alpha = dfdx(f2, x_min);
    double beta  = dfdx(f2, x_max);

    for( int N : num_nodes) {
        double h = (x_max - x_min) / (N - 1);
        std::vector<double> xx(N + 6); // z dołożonymi wezlami
        std::vector<double> xw(N + 4);
        std::vector<double> yw(N + 4);

        // WEZLY
        for (int i = -2; i <= (N + 3); ++i)
            xx[i+2] = x_min + h * (i-1);


        for (int i = 1; i <= (N + 4); ++i)
            xw[i-1] = xx[i+1];
        for (int i = 0; i <= (N + 3); ++i){
            yw[i] = f2(xw[i]);
        }
        saveNodesToFile(xw, yw, N);


        // ROZWIAZNANIE UKL ROWNAN
        gsl_matrix *A = gsl_matrix_alloc(N, N);
        gsl_vector *b = gsl_vector_alloc(N);
        gsl_vector *c_gsl = gsl_vector_alloc(N);

        // Wypełnienie macierzy A i wektora b
        for (int i = 0; i < N; ++i) {
            if (i == 0 || i == N-1) {
                gsl_matrix_set(A, i, i, 4.0);
                if (i == 0) {
                    gsl_matrix_set(A, i, i + 1, 2.0);
                } else {
                    gsl_matrix_set(A, i, i - 1, 2.0);
                }
                gsl_vector_set(
                        b, i, i == 0 ? f2(xw[i+1]) + alpha*h / 3 : f2(xw[i+1]) - beta*h / 3
                );
            } else {
                gsl_matrix_set(A, i, i, 4.0);
                gsl_matrix_set(A, i, i - 1, 1.0);
                gsl_matrix_set(A, i, i + 1, 1.0);
                gsl_vector_set(b, i, f2(xw[i+1]));
            }
        }

        gsl_linalg_HH_solve(A, b, c_gsl);

        vector<double> c = convert_gsl_to_vector(c_gsl, N);

        double step = 0.1;
        ofstream file("data/interpolation_results_" + to_string(N) + "f_2.txt");
        file << "x y\n";

        double c0 = c[1] - h/3*alpha;
        double cn_plus_1 = c[ c.size() -2] + h/3*beta;

        c.insert(c.begin(), c0);
        c.push_back(cn_plus_1);

       for (double x = x_min; x <= x_max; x += step) {
            double s_x = interpolate(x, c, xx, h);
            file << x << " " << s_x << "\n";
        }
        file.close();

        gsl_matrix_free(A);
        gsl_vector_free(b);
        gsl_vector_free(c_gsl);
    }

    return 0;
}