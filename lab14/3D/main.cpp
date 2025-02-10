#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

double gen_1()
{
    static long x = 10;
    int a = 17;
    long m = pow(2, 13) - 1;
    x = (a * x) % m;
    return double(x) / (m + 1.0);
}

double gen_2()
{
    static long x = 10;
    int a = 85;
    long m = pow(2, 13) - 1;
    x = (a * x) % m;
    return double(x) / (m + 1.0);
}

double gen_3()
{
    static long x_2 = 10, x_1 = 10, x_0 = 10;
    long a1 = 1176, a2 = 1476, a3 = 1776;
    long m = pow(2, 32) - 5;
    long x = (a1 * x_0 + a2 * x_1 + a3 * x_2) % m;
    x_2 = x_1;
    x_1 = x_0;
    x_0 = x;
    return double(x) / (m + 1.0);
}

void save_to_file(const char *filename, double data[], int n)
{
    ofstream outFile(filename);
    for (int i = 0; i < n; ++i)
    {
        outFile << data[i] << " ";        
    }
    cout << "Zapisano do pliku o nazwie: " << filename << endl;
    outFile.close();
}

struct Vector3D
{
    double x, y, z;

    void normalize()
    {
        double magnitude = sqrt(x * x + y * y + z * z);
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }

    void scale(double factor)
    {
        x *= factor;
        y *= factor;
        z *= factor;
    }
};

Vector3D generate_vector()
{
    double u1 = gen_3(), u2 = gen_3();
    double u3 = gen_3(), u4 = gen_3();
    Vector3D v;

    v.x = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2);
    v.y = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2);
    v.z = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4);

    v.normalize(); 
    return v;
}

Vector3D generate_vector_on_sphere()
{
    double u1 = gen_3(), u2 = gen_3();
    double u3 = gen_3(), u4 = gen_3();
    Vector3D v;

    v.x = sqrt(-2 * log(1 - u1)) * cos(2 * M_PI * u2);
    v.y = sqrt(-2 * log(1 - u1)) * sin(2 * M_PI * u2);
    v.z = sqrt(-2 * log(1 - u3)) * cos(2 * M_PI * u4);

    v.normalize();
    return v;
}

Vector3D generate_point_in_ball()
{
    Vector3D v = generate_vector_on_sphere();
    double u = gen_3();           
    double s = pow(u, 1.0 / 3.0); 
    v.scale(s);                   
    return v;
}

void calculate_and_save_density(std::vector<Vector3D>& points, int N, const std::string& filename){
    const int K = 10;
    double Delta = 1.0 / K;
    int counts[K] = {0};
    std::ofstream outFile(filename);

    for (int i = 0; i < N; i++) {
        double radius = sqrt(points[i].x * points[i].x + points[i].y * points[i].y + points[i].z * points[i].z);
        int index = int(radius / Delta);
        if (index >= K)
            index = K - 1;
        counts[index]++;
    }

    for (int j = 0; j < K; j++) {
        double Rj = Delta * (j + 1);
        double Rj_minus_1 = Delta * j;
        double Vj = (4.0 / 3.0) * M_PI * pow(Rj, 3);
        double Vj_minus_1 = (4.0 / 3.0) * M_PI * pow(Rj_minus_1, 3);
        double volume = Vj - Vj_minus_1;
        double density = counts[j] / volume;
        outFile << "Przedział " << j + 1 << ": Liczność = " << counts[j] << ", Gęstość = " << density << "\n";
    }
    outFile.close();
}

int main()
{
    const int NUM_POINTS = 2000;
    const int K = 10;
    Vector3D points_on_sphere[NUM_POINTS];
    Vector3D points_in_ball[NUM_POINTS];

    std::ofstream outFileSphere("normalized_vectors_on_sphere.txt");
    std::ofstream outFileBall("points_inside_ball.txt");

    for (int i = 0; i < NUM_POINTS; i++)
    {
        points_on_sphere[i] = generate_vector_on_sphere();
        outFileSphere << points_on_sphere[i].x << " " << points_on_sphere[i].y << " " << points_on_sphere[i].z << "\n";
        points_in_ball[i] = generate_point_in_ball();
        outFileBall << points_in_ball[i].x << " " << points_in_ball[i].y << " " << points_in_ball[i].z << "\n";
    }

    outFileSphere.close();
    outFileBall.close();

    const std::vector<int> N_values = {2000, 10000, 10000000};
    for (int N : N_values) {
        std::vector<Vector3D> points(N);
        for (int i = 0; i < N; i++) {
            points[i] = generate_point_in_ball();
        }
        std::string filename = "density_distribution_N_" + std::to_string(N) + ".txt";
        calculate_and_save_density(points, N, filename);
    }

    return 0;
}
