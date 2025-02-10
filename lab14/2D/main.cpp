#include <cmath>
#include <iostream>
#include <fstream>

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

int main()
{
    const int NUM_POINTS = 2000;
    const int K = 10;
    double p1[2000];
    double p2[2000];
    double p3[2000];

    for(int i = 0; i < NUM_POINTS; i++)
    {
        p1[i] = gen_1();
        p2[i] = gen_2();
        p3[i] = gen_3();
    }
    
    std::ofstream out1("p1i1.txt");
    std::ofstream out2("p1i2.txt");
    std::ofstream out3("p1i3.txt");
    std::ofstream out4("p2i1.txt");
    std::ofstream out5("p2i2.txt");
    std::ofstream out6("p2i3.txt");
    std::ofstream out7("p3i1.txt");
    std::ofstream out8("p3i2.txt");
    std::ofstream out9("p3i3.txt");

    for (int i = 0; i < NUM_POINTS - 3; i++)
    {
        out1 << p1[i] << " " << p1[i + 1] << "\n";
        out2 << p1[i] << " " << p1[i + 2] << "\n";
        out3 << p1[i] << " " << p1[i + 3] << "\n";
        out4 << p2[i] << " " << p2[i + 1] << "\n";
        out5 << p2[i] << " " << p2[i + 2] << "\n";
        out6 << p2[i] << " " << p2[i + 3] << "\n";
        out7 << p3[i] << " " << p3[i + 1] << "\n";
        out8 << p3[i] << " " << p3[i + 2] << "\n";
        out9 << p3[i] << " " << p3[i + 3] << "\n";
    }

    out1.close();
    out2.close();
    out3.close();
    out4.close();
    out5.close();
    out6.close();
    out7.close();
    out9.close();
    out9.close();

    return 0;
}
